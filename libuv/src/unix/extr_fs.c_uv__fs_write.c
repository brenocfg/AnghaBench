#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ off; int nbufs; TYPE_1__* bufs; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ uv_fs_t ;
struct iovec {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int pwritev (int /*<<< orphan*/ ,struct iovec*,int,scalar_t__) ; 
 int uv__pwritev (int /*<<< orphan*/ ,struct iovec*,int,scalar_t__) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

__attribute__((used)) static ssize_t uv__fs_write(uv_fs_t* req) {
#if defined(__linux__)
  static int no_pwritev;
#endif
  ssize_t r;

  /* Serialize writes on OS X, concurrent write() and pwrite() calls result in
   * data loss. We can't use a per-file descriptor lock, the descriptor may be
   * a dup().
   */
#if defined(__APPLE__)
  static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  if (pthread_mutex_lock(&lock))
    abort();
#endif

  if (req->off < 0) {
    if (req->nbufs == 1)
      r = write(req->file, req->bufs[0].base, req->bufs[0].len);
    else
      r = writev(req->file, (struct iovec*) req->bufs, req->nbufs);
  } else {
    if (req->nbufs == 1) {
      r = pwrite(req->file, req->bufs[0].base, req->bufs[0].len, req->off);
      goto done;
    }
#if HAVE_PREADV
    r = pwritev(req->file, (struct iovec*) req->bufs, req->nbufs, req->off);
#else
# if defined(__linux__)
    if (no_pwritev) retry:
# endif
    {
      r = pwrite(req->file, req->bufs[0].base, req->bufs[0].len, req->off);
    }
# if defined(__linux__)
    else {
      r = uv__pwritev(req->file,
                      (struct iovec*) req->bufs,
                      req->nbufs,
                      req->off);
      if (r == -1 && errno == ENOSYS) {
        no_pwritev = 1;
        goto retry;
      }
    }
# endif
#endif
  }

done:
#if defined(__APPLE__)
  if (pthread_mutex_unlock(&lock))
    abort();
#endif

  return r;
}