#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct bundle {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogTIMER ; 
 int /*<<< orphan*/  bundle_CleanDatalinks (struct bundle*) ; 
 int /*<<< orphan*/  bundle_Exception (struct bundle*,int) ; 
 scalar_t__ bundle_IsDead (struct bundle*) ; 
 scalar_t__ descriptor_IsSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  descriptor_Read (int /*<<< orphan*/ *,struct bundle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  descriptor_UpdateSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ descriptor_Write (int /*<<< orphan*/ *,struct bundle*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * mkfdset () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 TYPE_1__ server ; 
 scalar_t__ sig_Handle () ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  zerofdset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DoLoop(struct bundle *bundle)
{
  fd_set *rfds, *wfds, *efds;
  int i, nfds, nothing_done;

  if ((rfds = mkfdset()) == NULL) {
    log_Printf(LogERROR, "DoLoop: Cannot create fd_set\n");
    return;
  }

  if ((wfds = mkfdset()) == NULL) {
    log_Printf(LogERROR, "DoLoop: Cannot create fd_set\n");
    free(rfds);
    return;
  }

  if ((efds = mkfdset()) == NULL) {
    log_Printf(LogERROR, "DoLoop: Cannot create fd_set\n");
    free(rfds);
    free(wfds);
    return;
  }

  for (; !bundle_IsDead(bundle); bundle_CleanDatalinks(bundle)) {
    nfds = 0;
    zerofdset(rfds);
    zerofdset(wfds);
    zerofdset(efds);

    /* All our datalinks, the tun device and the MP socket */
    descriptor_UpdateSet(&bundle->desc, rfds, wfds, efds, &nfds);

    /* All our prompts and the diagnostic socket */
    descriptor_UpdateSet(&server.desc, rfds, NULL, NULL, &nfds);

    bundle_CleanDatalinks(bundle);
    if (bundle_IsDead(bundle))
      /* Don't select - we'll be here forever */
      break;

    /*
     * It's possible that we've had a signal since we last checked.  If
     * we don't check again before calling select(), we may end up stuck
     * after having missed the event.... sig_Handle() tries to be as
     * quick as possible if nothing is likely to have happened.
     * This is only really likely if we block in open(... O_NONBLOCK)
     * which will happen with a misconfigured device.
     */
    if (sig_Handle())
      continue;

    i = select(nfds, rfds, wfds, efds, NULL);

    if (i < 0 && errno != EINTR) {
      log_Printf(LogERROR, "DoLoop: select(): %s\n", strerror(errno));
      if (log_IsKept(LogTIMER)) {
        struct timeval t;

        for (i = 0; i <= nfds; i++) {
          if (FD_ISSET(i, rfds)) {
            log_Printf(LogTIMER, "Read set contains %d\n", i);
            FD_CLR(i, rfds);
            t.tv_sec = t.tv_usec = 0;
            if (select(nfds, rfds, wfds, efds, &t) != -1) {
              log_Printf(LogTIMER, "The culprit !\n");
              break;
            }
          }
          if (FD_ISSET(i, wfds)) {
            log_Printf(LogTIMER, "Write set contains %d\n", i);
            FD_CLR(i, wfds);
            t.tv_sec = t.tv_usec = 0;
            if (select(nfds, rfds, wfds, efds, &t) != -1) {
              log_Printf(LogTIMER, "The culprit !\n");
              break;
            }
          }
          if (FD_ISSET(i, efds)) {
            log_Printf(LogTIMER, "Error set contains %d\n", i);
            FD_CLR(i, efds);
            t.tv_sec = t.tv_usec = 0;
            if (select(nfds, rfds, wfds, efds, &t) != -1) {
              log_Printf(LogTIMER, "The culprit !\n");
              break;
            }
          }
        }
      }
      break;
    }

    log_Printf(LogTIMER, "Select returns %d\n", i);

    sig_Handle();

    if (i <= 0)
      continue;

    for (i = 0; i <= nfds; i++)
      if (FD_ISSET(i, efds)) {
        log_Printf(LogPHASE, "Exception detected on descriptor %d\n", i);
        /* We deal gracefully with link descriptor exceptions */
        if (!bundle_Exception(bundle, i)) {
          log_Printf(LogERROR, "Exception cannot be handled !\n");
          break;
        }
      }

    if (i <= nfds)
      break;

    nothing_done = 1;

    if (descriptor_IsSet(&server.desc, rfds)) {
      descriptor_Read(&server.desc, bundle, rfds);
      nothing_done = 0;
    }

    if (descriptor_IsSet(&bundle->desc, rfds)) {
      descriptor_Read(&bundle->desc, bundle, rfds);
      nothing_done = 0;
    }

    if (descriptor_IsSet(&bundle->desc, wfds))
      if (descriptor_Write(&bundle->desc, bundle, wfds) <= 0 && nothing_done) {
        /*
         * This is disastrous.  The OS has told us that something is
         * writable, and all our write()s have failed.  Rather than
         * going back immediately to do our UpdateSet()s and select(),
         * we sleep for a bit to avoid gobbling up all cpu time.
         */
        struct timeval t;

        t.tv_sec = 0;
        t.tv_usec = 100000;
        select(0, NULL, NULL, NULL, &t);
      }
  }

  log_Printf(LogDEBUG, "DoLoop done.\n");
}