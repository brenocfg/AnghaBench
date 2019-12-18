#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct aiocb {int dummy; } ;
struct TYPE_11__ {int aio_fildes; } ;
struct TYPE_9__ {int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_10__ {int aio_fildes; TYPE_1__ aio_sigevent; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  O_DSYNC ; 
 int /*<<< orphan*/  SIGEV_NONE ; 
 int /*<<< orphan*/  aio_cancel (int,TYPE_2__*) ; 
 int aio_error (TYPE_2__*) ; 
 scalar_t__ aio_fsync (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int aio_return (TYPE_2__*) ; 
 scalar_t__ binlog_disabled ; 
 int binlog_fd ; 
 scalar_t__ binlog_sync_active ; 
 TYPE_2__ binlog_sync_aiocb ; 
 scalar_t__ binlog_sync_last ; 
 TYPE_3__ binlog_write_aiocb ; 
 char* binlogname ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void sync_binlog (int mode) {
  int res, err;
  if (!binlogname || binlog_disabled) {
    return;
  }
  if (binlog_sync_active) {
    res = err = aio_error (&binlog_sync_aiocb);
    if (res == EINPROGRESS && now > binlog_sync_active + 120) {
      fprintf (stderr, "%d binlog aio_sync didn't complete for 120 seconds, invoking fsync()!\n", now);
      aio_cancel (binlog_sync_aiocb.aio_fildes, &binlog_sync_aiocb);
      fsync (binlog_sync_aiocb.aio_fildes);
      exit (3);
    }
    if (res != EINPROGRESS) {
      binlog_sync_active = 0;
      res = aio_return (&binlog_sync_aiocb);
      if (res >= 0) {
        binlog_sync_last = now;
        if (binlog_sync_aiocb.aio_fildes != binlog_fd && binlog_write_aiocb.aio_fildes != binlog_sync_aiocb.aio_fildes) {
          close (binlog_sync_aiocb.aio_fildes);
        }
        binlog_sync_aiocb.aio_fildes = -1;
        if (verbosity > 1) {
          fprintf (stderr, "%d aio_fsync() for binlog completed successfully\n", now);
        }
      } else {
        errno = err;
        fprintf (stderr, "%d error syncing binlog %s: %m\n", now, binlogname);
        fsync (binlog_sync_aiocb.aio_fildes);
        exit (3);
      }
    }
  }
  if (!binlog_sync_active && mode == 1) {
    memset (&binlog_sync_aiocb, 0, sizeof (struct aiocb));
    binlog_sync_aiocb.aio_fildes = binlog_fd;
    binlog_sync_aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
    if (aio_fsync (O_DSYNC, &binlog_sync_aiocb) < 0) {
      fprintf (stderr, "%d aio_fsync() for binlog failed: %m\n", now);
      fsync (binlog_fd);
      exit (3);
    }
    binlog_sync_active = now;
    if (verbosity > 1) {
      fprintf (stderr, "%d queued aio_fsync() for binlog\n", now);
    }
  }
  if (mode >= 2) {
    if (fsync (binlog_fd) < 0) {
      fprintf (stderr, "%d error syncing binlog: %m", now);
    } else {
      binlog_sync_last = now;
      if (verbosity > 1) {
        fprintf (stderr, "%d binlog sync ok\n", now);
      }
    }
  }
}