#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct aiocb {int dummy; } ;
struct TYPE_7__ {int aio_fildes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EINPROGRESS ; 
 int MAX_PRIORITY ; 
 int /*<<< orphan*/  O_DSYNC ; 
 int /*<<< orphan*/  aio_cancel (int,TYPE_1__*) ; 
 int aio_error (TYPE_1__*) ; 
 scalar_t__ aio_fsync (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int aio_return (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int* fd ; 
 char** fnames ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 scalar_t__ fsync (int) ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/ ** letter_stat ; 
 scalar_t__ log_drive ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  save_index () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__* sync_active ; 
 TYPE_1__* sync_aiocb ; 
 scalar_t__* sync_last ; 
 int verbosity ; 

void flush_all (int force) {
  save_index();

  double tm = -get_utime (CLOCK_MONOTONIC);
  int i;
  int res;
  int was_error = 0;

  for (i = 0; i <= MAX_PRIORITY; i++) {
    if (sync_active[i]) {
      res = aio_error (&sync_aiocb[i]);
      if (res == EINPROGRESS && now > sync_active[i] + 120) {
        fprintf (stderr, "%d aio_sync didn't complete for 120 seconds, invoking fsync()!\n", now);
        aio_cancel (sync_aiocb[i].aio_fildes, &sync_aiocb[i]);
        fsync (sync_aiocb[i].aio_fildes);
        was_error = 1;
      }
      if (res != EINPROGRESS) {
        sync_active[i] = 0;
        res = aio_return (&sync_aiocb[i]);
        if (res >= 0) {
          sync_last[i] = now;
          sync_aiocb[i].aio_fildes = -1;
          if (verbosity > 1) {
            fprintf (stderr, "%d aio_fsync() completed successfully\n", now);
          }
        } else {
          fprintf (stderr, "%d error syncing %s: %m\n", now, fnames[i + 1]);
          fsync (sync_aiocb[i].aio_fildes);
          was_error = 1;
        }
      }
    }

    if (!sync_active[i] && !force) {
      memset (&sync_aiocb[i], 0, sizeof (struct aiocb));
      sync_aiocb[i].aio_fildes = fd[i + 1];
      if (aio_fsync (O_DSYNC, &sync_aiocb[i]) < 0) {
        fprintf (stderr, "%d aio_fsync() for %s failed: %m\n", now, fnames[i + 1]);
        fsync (fd[i + 1]);
        was_error = 1;
      }
      sync_active[i] = now;
      if (i > 0) {
        letter_stat[i - 1][5]++;
      }
      if (verbosity > 1 || log_drive) {
        kprintf ("%d queued aio_fsync() for %s\n", now, fnames[i + 1]);
      }
    }
    if (force) {
      if (fsync (fd[i + 1]) < 0) {
        fprintf (stderr, "%d error syncing %s: %m", now, fnames[i + 1]);
      } else {
        sync_last[i] = now;
        if (verbosity > 1) {
          fprintf (stderr, "%d sync ok for %s\n", now, fnames[i + 1]);
        }
      }
    }
//    assert (fsync (fd[i + 1]) >= 0);
  }

  if (was_error) {
    was_error = 0;
    for (i = 0; i <= MAX_PRIORITY; i++) {
      if (fsync (fd[i + 1]) < 0) {
        fprintf (stderr, "%d error resyncing %s: %m", now, fnames[i + 1]);
        was_error = 1;
      }
    }
    if (was_error) {
      exit (3);
    }
  }

  tm += get_utime (CLOCK_MONOTONIC);
  if (tm >= 0.1) {
    fprintf (stderr, "Warning. fsync time = %.9lf at time %d\n", tm, now);
  }
}