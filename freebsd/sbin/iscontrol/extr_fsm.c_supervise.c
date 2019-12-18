#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int trans_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  fd; TYPE_1__* op; } ;
typedef  TYPE_2__ isess_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pidfile; int /*<<< orphan*/  sessionType; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSIRESTART ; 
 int /*<<< orphan*/  ISCSISIGNAL ; 
 int /*<<< orphan*/  ISCSISTART ; 
 int /*<<< orphan*/  ISCSISTOP ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_KERN ; 
 int LOG_NDELAY ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int SESS_DISCONNECT ; 
 int SESS_FULLFEATURE ; 
 int SESS_INITIALLOGIN1 ; 
 int SESS_RECONNECT ; 
 int SESS_REDIRECT ; 
 int SIGHUP ; 
 int SIGINT ; 
 int SIGTERM ; 
 int SIGUSR1 ; 
 int T15 ; 
 int T8 ; 
 int T9 ; 
 TYPE_2__* currsess ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ doCAM (TYPE_2__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ setOptions (TYPE_2__*,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  trap ; 
 scalar_t__ vflag ; 

__attribute__((used)) static trans_t
supervise(isess_t *sess)
{
     int	sig, val;

     debug_called(3);

     if(strcmp(sess->op->sessionType, "Discovery") == 0) {
	  sess->flags |= SESS_DISCONNECT;
	  return T9;
     }

     if(vflag)
	  printf("ready to go scsi\n");

     if(setOptions(sess, SESS_FULLFEATURE) != 0)
	  return 0; // failure

     if((sess->flags & SESS_FULLFEATURE) == 0) {
	  if(daemon(0, 1) != 0) {
	       perror("daemon");
	       exit(1);
	  }
	  if(sess->op->pidfile != NULL) {
	       FILE *pidf;

	       pidf = fopen(sess->op->pidfile, "w");
	       if(pidf != NULL) { 
 		    fprintf(pidf, "%d\n", getpid());
		    fclose(pidf);
	       }
	  }
	  openlog("iscontrol", LOG_CONS|LOG_PERROR|LOG_PID|LOG_NDELAY, LOG_KERN);
	  syslog(LOG_INFO, "running");

	  currsess = sess;
	  if(ioctl(sess->fd, ISCSISTART)) {
	       perror("ISCSISTART");
	       return -1;
	  }
	  if(doCAM(sess) == 0) {
	       syslog(LOG_WARNING, "no device found");
	       ioctl(sess->fd, ISCSISTOP);
	       return T15;
	  }

     }
     else {
	  if(ioctl(sess->fd, ISCSIRESTART)) {
	       perror("ISCSIRESTART");
	       return -1;
	  }
     }
	  
     signal(SIGINT, trap);
     signal(SIGHUP, trap);
     signal(SIGTERM, trap);

     sig = SIGUSR1;
     signal(sig, trap);
     if(ioctl(sess->fd, ISCSISIGNAL, &sig)) {
	  perror("ISCSISIGNAL");
	  return -1;
     }
     sess->flags |= SESS_FULLFEATURE;

     sess->flags &= ~(SESS_REDIRECT | SESS_RECONNECT);
     if(vflag)
	  printf("iscontrol: supervise starting main loop\n");
     /*
      | the main loop - actually do nothing
      | all the work is done inside the kernel
      */
     while((sess->flags & (SESS_REDIRECT|SESS_RECONNECT|SESS_DISCONNECT)) == 0) {
	  // do something?
	  // like sending a nop_out?
	  sleep(60);
     }
     printf("iscontrol: supervise going down\n");
     syslog(LOG_INFO, "sess flags=%x", sess->flags);

     sig = 0;
     if(ioctl(sess->fd, ISCSISIGNAL, &sig)) {
	  perror("ISCSISIGNAL");
     }

     if(sess->flags & SESS_DISCONNECT) {
	  sess->flags &= ~SESS_FULLFEATURE;
	  return T9;
     } 
     else {
	  val = 0;
	  if(ioctl(sess->fd, ISCSISTOP, &val)) {
	       perror("ISCSISTOP");
	  }
	  sess->flags |= SESS_INITIALLOGIN1;
     }
     return T8;
}