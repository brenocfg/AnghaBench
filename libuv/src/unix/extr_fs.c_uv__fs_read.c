#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int nbufs; scalar_t__ off; int /*<<< orphan*/  file; TYPE_3__* bufs; TYPE_3__* bufsml; } ;
typedef  TYPE_1__ uv_fs_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct iovec {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EOPNOTSUPP ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int pread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int preadv (int /*<<< orphan*/ ,struct iovec*,int,scalar_t__) ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readv (int /*<<< orphan*/ ,struct iovec*,int) ; 
 int /*<<< orphan*/  uv__free (TYPE_3__*) ; 
 int uv__fs_preadv (int /*<<< orphan*/ ,TYPE_3__*,int,scalar_t__) ; 
 unsigned int uv__getiovmax () ; 
 int uv__preadv (int /*<<< orphan*/ ,struct iovec*,int,scalar_t__) ; 

__attribute__((used)) static ssize_t uv__fs_read(uv_fs_t* req) {
#if defined(__linux__)
  static int no_preadv;
#endif
  unsigned int iovmax;
  ssize_t result;

  iovmax = uv__getiovmax();
  if (req->nbufs > iovmax)
    req->nbufs = iovmax;

  if (req->off < 0) {
    if (req->nbufs == 1)
      result = read(req->file, req->bufs[0].base, req->bufs[0].len);
    else
      result = readv(req->file, (struct iovec*) req->bufs, req->nbufs);
  } else {
    if (req->nbufs == 1) {
      result = pread(req->file, req->bufs[0].base, req->bufs[0].len, req->off);
      goto done;
    }

#if HAVE_PREADV
    result = preadv(req->file, (struct iovec*) req->bufs, req->nbufs, req->off);
#else
# if defined(__linux__)
    if (no_preadv) retry:
# endif
    {
      result = uv__fs_preadv(req->file, req->bufs, req->nbufs, req->off);
    }
# if defined(__linux__)
    else {
      result = uv__preadv(req->file,
                          (struct iovec*)req->bufs,
                          req->nbufs,
                          req->off);
      if (result == -1 && errno == ENOSYS) {
        no_preadv = 1;
        goto retry;
      }
    }
# endif
#endif
  }

done:
  /* Early cleanup of bufs allocation, since we're done with it. */
  if (req->bufs != req->bufsml)
    uv__free(req->bufs);

  req->bufs = NULL;
  req->nbufs = 0;

#ifdef __PASE__
  /* PASE returns EOPNOTSUPP when reading a directory, convert to EISDIR */
  if (result == -1 && errno == EOPNOTSUPP) {
    struct stat buf;
    ssize_t rc;
    rc = fstat(req->file, &buf);
    if (rc == 0 && S_ISDIR(buf.st_mode)) {
      errno = EISDIR;
    }
  }
#endif

  return result;
}