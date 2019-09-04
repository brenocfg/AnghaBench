#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct aiocb {int dummy; } ;
struct TYPE_18__ {int aio_fildes; } ;
struct TYPE_17__ {TYPE_1__* info; } ;
struct TYPE_15__ {int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_16__ {int aio_fildes; int aio_nbytes; long long aio_offset; int aio_buf; TYPE_2__ aio_sigevent; } ;
struct TYPE_14__ {int file_size; } ;
struct TYPE_13__ {int log_rptr; int log_endw; int log_wptr; int log_start; int log_wcrypt_ptr; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  SIGEV_NONE ; 
 TYPE_11__ W ; 
 int /*<<< orphan*/  aio_cancel (int,TYPE_3__*) ; 
 int aio_error (TYPE_3__*) ; 
 int aio_return (TYPE_3__*) ; 
 scalar_t__ aio_write (TYPE_3__*) ; 
 int aio_write_start ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_cyclic_mode ; 
 scalar_t__ binlog_disabled ; 
 int binlog_fd ; 
 TYPE_6__ binlog_sync_aiocb ; 
 scalar_t__ binlog_write_active ; 
 TYPE_3__ binlog_write_aiocb ; 
 scalar_t__ binlog_write_last ; 
 char* binlogname ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_binlog_forced (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kfs_buffer_crypt (TYPE_4__*,int,int,int) ; 
 long long log_headers_size ; 
 long long log_pos ; 
 long long log_start_pos ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  relax_write_log_crc32 () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sync_binlog (int) ; 
 int verbosity ; 

void flush_binlog (void) {
  int res, err;
  int force_sync = 0;
  if (!binlogname || binlog_disabled) {
    return;
  }
  if (binlog_write_active) {
    res = err = aio_error (&binlog_write_aiocb);
    if (res == EINPROGRESS && now > binlog_write_active + 120) {
      fprintf (stderr, "%d binlog aio_write didn't complete for 120 seconds, invoking write()!\n", now);
      aio_cancel (binlog_write_aiocb.aio_fildes, &binlog_write_aiocb);
      flush_binlog_forced (1);
      exit (3);
    }
    if (res != EINPROGRESS) {
      binlog_write_active = 0;
      res = aio_return (&binlog_write_aiocb);
      if (res >= 0) {
        assert (res <= binlog_write_aiocb.aio_nbytes);
        binlog_write_last = now;
        if (binlog_write_aiocb.aio_fildes != binlog_fd && binlog_write_aiocb.aio_fildes != binlog_sync_aiocb.aio_fildes) {
          close (binlog_write_aiocb.aio_fildes);
        }
        binlog_write_aiocb.aio_fildes = -1;
        assert (aio_write_start);

        if (W.log_rptr == aio_write_start) {
          log_pos += res;
          W.log_rptr += res;
          if (Binlog && !binlog_cyclic_mode) {
            //Binlog->info->log_pos += res;
            Binlog->info->file_size += res;
          }
          assert ((!W.log_endw && W.log_rptr <= W.log_wptr) || W.log_rptr <= W.log_endw);
          if (W.log_rptr == W.log_endw) {
            W.log_rptr = W.log_start;
            W.log_endw = 0;
          }
        }

        aio_write_start = 0;
        force_sync = 1;

        if (verbosity > 1) {
          fprintf (stderr, "%d aio_write() for binlog (position=%lld, size=%ld) completed successfully, %d bytes written\n", now, (long long) binlog_write_aiocb.aio_offset, (long) binlog_write_aiocb.aio_nbytes, res);
        }
      } else {
        errno = err;
        fprintf (stderr, "%d error writing binlog %s (position=%lld, size=%ld): %m\n", now, binlogname, (long long) binlog_write_aiocb.aio_offset, (long) binlog_write_aiocb.aio_nbytes);
        flush_binlog_forced (1);
        exit (3);
      }
    }
  }
  if (!binlog_write_active && W.log_rptr != W.log_wptr) {
    long long log_file_pos = log_pos - log_start_pos + log_headers_size;
    int w, t;
    // assert (lseek (binlog_fd, log_file_pos, SEEK_SET) == log_file_pos);

    if (W.log_endw) {
      if (W.log_rptr <= W.log_wcrypt_ptr && W.log_wcrypt_ptr < W.log_endw) {
        t = W.log_endw - W.log_wcrypt_ptr;
        relax_write_log_crc32 (); /* relax crc32 before encryption */
        kfs_buffer_crypt (Binlog, W.log_wcrypt_ptr, t, log_file_pos + (W.log_wcrypt_ptr - W.log_rptr));
        W.log_wcrypt_ptr = W.log_start;
      }
      w = W.log_endw - W.log_rptr;
      if (!w) {
        W.log_rptr = W.log_start;
        W.log_endw = 0;
      }
    }
    if (!W.log_endw) {
      if (W.log_rptr <= W.log_wcrypt_ptr && W.log_wcrypt_ptr < W.log_wptr) {
        t = W.log_wptr - W.log_wcrypt_ptr;
        relax_write_log_crc32 (); /* relax crc32 before encryption */
        kfs_buffer_crypt (Binlog, W.log_wcrypt_ptr, t, log_file_pos + (W.log_wcrypt_ptr - W.log_rptr));
        W.log_wcrypt_ptr = W.log_wptr;
      }
      w = W.log_wptr - W.log_rptr;
    }

    assert (w >= 0);

    if (w > 0) {
      memset (&binlog_write_aiocb, 0, sizeof (struct aiocb));
      binlog_write_aiocb.aio_fildes = binlog_fd;
      binlog_write_aiocb.aio_offset = log_file_pos;
      binlog_write_aiocb.aio_nbytes = w;
      binlog_write_aiocb.aio_buf = W.log_rptr;
      binlog_write_aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;

      if (aio_write (&binlog_write_aiocb) < 0) {
        fprintf (stderr, "%d aio_write() for binlog (position=%lld, size=%d) failed: %m\n", now, log_file_pos, w);
        flush_binlog_forced (1);
        exit (3);
      }

      binlog_write_active = now;
      aio_write_start = W.log_rptr;

      if (verbosity > 1) {
        fprintf (stderr, "%d queued aio_write() for binlog (position=%lld, size=%d)\n", now, log_file_pos, w);
      }
    }
  }

  sync_binlog (force_sync);

}