/* config.h:  a general config file */

/* configuration files.  I rdist the first one and leave machine
   specific stuff in the second one */

#define CONFIGFILE "/etc/ece-snmpd.conf"          /* default config file */
#define CONFIGFILETWO "/etc/ece-snmpd.local.conf" /* optional second file */

/* to hack in forced V2 security, I had to reserve the left byte of
   the ACL Mib word for V2.  Do NOT define more than 5 V1 communities
   else they will roll into these definitions (see snmp_vars.c:340) */
   
/* don't change these values! */
#define SNMPV1      0xAAAA       /* readable by anyone */
#define SNMPV2ANY   0xA000       /* V2 Any type (includes NoAuth) */
#define SNMPV2AUTH  0x8000       /* V2 Authenticated requests only */

/* If GLOBALSECURITY is defined, it sets the default SNMP access type
   for the extensible mibs to the setting type described. */

#define GLOBALSECURITY SNMPV2AUTH    /* only authenticated snmpv2 requests
                                        permited */


/* the ErrorFlag is V1 accessable because HP Openview does not support
V2.  You can make this list of pairs as long as you want, just make
sure to end it in -1.*/

#define SECURITYEXCEPTIONS {100,SNMPV1,-1} /* the ErrorFlag is V1

/* additional note:  if SECURITYEXCEPTIONS is defined, you must use an
                     ANSI compiler (gcc) for agent/extensible/extensible.c */


/* Mib-2 tree Info */

/* These are the system information variables. */

#if defined(hpux)
#define VERS_DESC   "HP-UX 9.0.5"
#elif defined(ultrix)
#define VERS_DESC   "Ultrix 4.2"
#else
#define VERS_DESC   "SunOS 4.1.4"
#endif

#define SYS_CONTACT "support@ece.ucdavis.edu"
#define SYS_NAME    "unknown"
#define SYS_LOC     "UCDavis Electrical Engineering Departement"

/* LOGFILE:  If defined it closes stdout/err/in and opens this in out/err's
   place.  (stdin is closed so that sh scripts won't wait for it) */

#define LOGFILE "/usr/adm/ece-snmpd.log"

/* mib pointer to the top of the extensible tree */
/* point this to the location in the tree your company/organization
   has been allocated.  If you don't have an official one (like me),
   just make one up that doesn't overlap with other mibs you are using
   on the system */

#define EXTENSIBLEMIB 1,3,6,1,4,10 /* location of the extensible mib tree */
#define EXTENSIBLENUM 6            /* count the above numbers */

/* comment out to turn off functionality for any of these: */
/* (See README for details) */

#define PROCMIBNUM 1              /*   proc PROCESSNAME [MAX] [MIN] */
#define SHELLMIBNUM 3             /*   exec/shell NAME COMMAND      */
#define MEMMIBNUM 4               /*   swap MIN                     */
#define DISKMIBNUM 6              /*   disk DISK MINSIZE            */
#define LOADAVEMIBNUM 7           /*   load 1 5 15                  */

#define VERSIONMIBNUM 100  /* which version are you using?
                              This mibloc will tell you */

#define ERRORMIBNUM 101     /* Reports errors the agent runs into
                               (typically its "can't fork, no mem" problems) */
#define ERRORTIMELENGTH 600 /* how long to wait for error querys
                               before reseting the error trap.*/

/* Command to generate ps output, the final column must be the process
   name withOUT arguments */

#if defined(hpux) || defined(SYSV)
#define PSCMD "/bin/ps -e"
#else
#define PSCMD "/bin/ps -axc"
#endif

/* Exec command to fix PROC problems */
/* %s will be replaced by the process name in error */

#define PROCFIXCMD "/usr/local/bin/perl /local/scripts/fixproc %s"

/* Exec command to fix EXEC problems */
/* %s will be replaced by the process name in error */

#define EXECFIXCMD "/usr/local/bin/perl /local/scripts/fixproc %s"

/* Should exec output Cashing be used (speeds up things greatly), and
   if so, After how many seconds should the cache re-newed?  Note:
   Don't define CASHETIME to disable cashing completely */

#define EXCACHETIME 30
#define CACHEFILE "/tmp/.snmp-exec-cache"
#define MAXCACHESIZE (200*80)   /* roughly 200 lines max */

#define MAXDISKS 10                      /* can't scan more than this number */

/* misc defaults */

#define DEFDISKMINIMUMSPACE 100000       /* default of 100 meg minimum
                                            if the minimum size is not
                                            specified in the config file */

#define DEFMAXLOADAVE 12.0      /* default maximum load average before error */

#define MAXREADCOUNT 20   /* max times to loop reading output from
                             execs.  Because of sleep(1)s, this will also
                             be time to wait (in seconds) for exec to finish */

#define SNMPBLOCK 0       /* Set to 1 if you want snmpgets to block and never
                             timeout.  Original CMU code had this
                             hardcoded into the code as = 1 */

#define LASTFIELD -1      /* internal define */

#include "agent/extensible/struct.h"
