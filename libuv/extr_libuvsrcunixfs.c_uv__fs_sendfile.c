#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int file; scalar_t__ off; TYPE_1__* bufsml; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 scalar_t__ ENOTSOCK ; 
 scalar_t__ EXDEV ; 
 scalar_t__ errno ; 
 int sendfile (int,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int uv__fs_sendfile_emul (TYPE_2__*) ; 

__attribute__((used)) static ssize_t uv__fs_sendfile(uv_fs_t* req) {
  int in_fd;
  int out_fd;

  in_fd = req->flags;
  out_fd = req->file;

#if defined(__linux__) || defined(__sun)
  {
    off_t off;
    ssize_t r;

    off = req->off;
    r = sendfile(out_fd, in_fd, &off, req->bufsml[0].len);

    /* sendfile() on SunOS returns EINVAL if the target fd is not a socket but
     * it still writes out data. Fortunately, we can detect it by checking if
     * the offset has been updated.
     */
    if (r != -1 || off > req->off) {
      r = off - req->off;
      req->off = off;
      return r;
    }

    if (errno == EINVAL ||
        errno == EIO ||
        errno == ENOTSOCK ||
        errno == EXDEV) {
      errno = 0;
      return uv__fs_sendfile_emul(req);
    }

    return -1;
  }
#elif defined(__APPLE__)           || \
      defined(__DragonFly__)       || \
      defined(__FreeBSD__)         || \
      defined(__FreeBSD_kernel__)
  {
    off_t len;
    ssize_t r;

    /* sendfile() on FreeBSD and Darwin returns EAGAIN if the target fd is in
     * non-blocking mode and not all data could be written. If a non-zero
     * number of bytes have been sent, we don't consider it an error.
     */

#if defined(__FreeBSD__) || defined(__DragonFly__)
    len = 0;
    r = sendfile(in_fd, out_fd, req->off, req->bufsml[0].len, NULL, &len, 0);
#elif defined(__FreeBSD_kernel__)
    len = 0;
    r = bsd_sendfile(in_fd,
                     out_fd,
                     req->off,
                     req->bufsml[0].len,
                     NULL,
                     &len,
                     0);
#else
    /* The darwin sendfile takes len as an input for the length to send,
     * so make sure to initialize it with the caller's value. */
    len = req->bufsml[0].len;
    r = sendfile(in_fd, out_fd, req->off, &len, NULL, 0);
#endif

     /*
     * The man page for sendfile(2) on DragonFly states that `len` contains
     * a meaningful value ONLY in case of EAGAIN and EINTR.
     * Nothing is said about it's value in case of other errors, so better
     * not depend on the potential wrong assumption that is was not modified
     * by the syscall.
     */
    if (r == 0 || ((errno == EAGAIN || errno == EINTR) && len != 0)) {
      req->off += len;
      return (ssize_t) len;
    }

    if (errno == EINVAL ||
        errno == EIO ||
        errno == ENOTSOCK ||
        errno == EXDEV) {
      errno = 0;
      return uv__fs_sendfile_emul(req);
    }

    return -1;
  }
#else
  /* Squelch compiler warnings. */
  (void) &in_fd;
  (void) &out_fd;

  return uv__fs_sendfile_emul(req);
#endif
}