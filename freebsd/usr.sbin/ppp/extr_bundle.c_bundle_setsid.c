#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct datalink {int /*<<< orphan*/  physical; int /*<<< orphan*/  state; struct datalink* next; } ;
struct bundle {struct datalink* links; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATALINK_CLOSED ; 
 int /*<<< orphan*/  ID0realuid () ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SetTitle (char*) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_ChangedPID (struct bundle*) ; 
 scalar_t__ bundle_IsDead (struct bundle*) ; 
 int /*<<< orphan*/  bundle_LockTun (struct bundle*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 int getdtablesize () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,long,...) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  physical_ChangedPid (int /*<<< orphan*/ ,scalar_t__) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_InitService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_TermService () ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
bundle_setsid(struct bundle *bundle, int holdsession)
{
  /*
   * Lose the current session.  This means getting rid of our pid
   * too so that the tty device will really go away, and any getty
   * etc will be allowed to restart.
   */
  pid_t pid, orig;
  int fds[2];
  char done;
  struct datalink *dl;

  if (!holdsession && bundle_IsDead(bundle)) {
    /*
     * No need to lose our session after all... we're going away anyway
     *
     * We should really stop the timer and pause if holdsession is set and
     * the bundle's dead, but that leaves other resources lying about :-(
     */
    return;
  }

  orig = getpid();
  if (pipe(fds) == -1) {
    log_Printf(LogERROR, "pipe: %s\n", strerror(errno));
    return;
  }
  switch ((pid = fork())) {
    case -1:
      log_Printf(LogERROR, "fork: %s\n", strerror(errno));
      close(fds[0]);
      close(fds[1]);
      return;
    case 0:
      close(fds[1]);
      read(fds[0], &done, 1);		/* uu_locks are mine ! */
      close(fds[0]);
      if (pipe(fds) == -1) {
        log_Printf(LogERROR, "pipe(2): %s\n", strerror(errno));
        return;
      }
      switch ((pid = fork())) {
        case -1:
          log_Printf(LogERROR, "fork(2): %s\n", strerror(errno));
          close(fds[0]);
          close(fds[1]);
          return;
        case 0:
          close(fds[1]);
          bundle_LockTun(bundle);	/* update pid */
          read(fds[0], &done, 1);	/* uu_locks are mine ! */
          close(fds[0]);
          setsid();
          bundle_ChangedPID(bundle);
          log_Printf(LogDEBUG, "%ld -> %ld: %s session control\n",
                     (long)orig, (long)getpid(),
                     holdsession ? "Passed" : "Dropped");
          timer_InitService(0);		/* Start the Timer Service */
          break;
        default:
          close(fds[0]);
          /* Give away all our physical locks (to the final process) */
          for (dl = bundle->links; dl; dl = dl->next)
            if (dl->state != DATALINK_CLOSED)
              physical_ChangedPid(dl->physical, pid);
          write(fds[1], "!", 1);	/* done */
          close(fds[1]);
          _exit(0);
          break;
      }
      break;
    default:
      close(fds[0]);
      /* Give away all our physical locks (to the intermediate process) */
      for (dl = bundle->links; dl; dl = dl->next)
        if (dl->state != DATALINK_CLOSED)
          physical_ChangedPid(dl->physical, pid);
      write(fds[1], "!", 1);	/* done */
      close(fds[1]);
      if (holdsession) {
        int fd, status;

        timer_TermService();
        signal(SIGPIPE, SIG_DFL);
        signal(SIGALRM, SIG_DFL);
        signal(SIGHUP, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        for (fd = getdtablesize(); fd >= 0; fd--)
          close(fd);
        /*
         * Reap the intermediate process.  As we're not exiting but the
         * intermediate is, we don't want it to become defunct.
         */
        waitpid(pid, &status, 0);
        /* Tweak our process arguments.... */
        SetTitle("session owner");
#ifndef NOSUID
        setuid(ID0realuid());
#endif
        /*
         * Hang around for a HUP.  This should happen as soon as the
         * ppp that we passed our ctty descriptor to closes it.
         * NOTE: If this process dies, the passed descriptor becomes
         *       invalid and will give a select() error by setting one
         *       of the error fds, aborting the other ppp.  We don't
         *       want that to happen !
         */
        pause();
      }
      _exit(0);
      break;
  }
}