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
struct TYPE_5__ {int flags; int file; size_t off; TYPE_1__* bufsml; } ;
typedef  TYPE_2__ uv_fs_t ;
struct pollfd {int fd; int events; int revents; } ;
typedef  size_t ssize_t ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {size_t len; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EIO ; 
 scalar_t__ ESPIPE ; 
 scalar_t__ EWOULDBLOCK ; 
 int POLLOUT ; 
 scalar_t__ errno ; 
 size_t poll (struct pollfd*,int,int) ; 
 size_t pread (int,char*,size_t,size_t) ; 
 size_t read (int,char*,size_t) ; 
 size_t write (int,char*,size_t) ; 

__attribute__((used)) static ssize_t uv__fs_sendfile_emul(uv_fs_t* req) {
  struct pollfd pfd;
  int use_pread;
  off_t offset;
  ssize_t nsent;
  ssize_t nread;
  ssize_t nwritten;
  size_t buflen;
  size_t len;
  ssize_t n;
  int in_fd;
  int out_fd;
  char buf[8192];

  len = req->bufsml[0].len;
  in_fd = req->flags;
  out_fd = req->file;
  offset = req->off;
  use_pread = 1;

  /* Here are the rules regarding errors:
   *
   * 1. Read errors are reported only if nsent==0, otherwise we return nsent.
   *    The user needs to know that some data has already been sent, to stop
   *    them from sending it twice.
   *
   * 2. Write errors are always reported. Write errors are bad because they
   *    mean data loss: we've read data but now we can't write it out.
   *
   * We try to use pread() and fall back to regular read() if the source fd
   * doesn't support positional reads, for example when it's a pipe fd.
   *
   * If we get EAGAIN when writing to the target fd, we poll() on it until
   * it becomes writable again.
   *
   * FIXME: If we get a write error when use_pread==1, it should be safe to
   *        return the number of sent bytes instead of an error because pread()
   *        is, in theory, idempotent. However, special files in /dev or /proc
   *        may support pread() but not necessarily return the same data on
   *        successive reads.
   *
   * FIXME: There is no way now to signal that we managed to send *some* data
   *        before a write error.
   */
  for (nsent = 0; (size_t) nsent < len; ) {
    buflen = len - nsent;

    if (buflen > sizeof(buf))
      buflen = sizeof(buf);

    do
      if (use_pread)
        nread = pread(in_fd, buf, buflen, offset);
      else
        nread = read(in_fd, buf, buflen);
    while (nread == -1 && errno == EINTR);

    if (nread == 0)
      goto out;

    if (nread == -1) {
      if (use_pread && nsent == 0 && (errno == EIO || errno == ESPIPE)) {
        use_pread = 0;
        continue;
      }

      if (nsent == 0)
        nsent = -1;

      goto out;
    }

    for (nwritten = 0; nwritten < nread; ) {
      do
        n = write(out_fd, buf + nwritten, nread - nwritten);
      while (n == -1 && errno == EINTR);

      if (n != -1) {
        nwritten += n;
        continue;
      }

      if (errno != EAGAIN && errno != EWOULDBLOCK) {
        nsent = -1;
        goto out;
      }

      pfd.fd = out_fd;
      pfd.events = POLLOUT;
      pfd.revents = 0;

      do
        n = poll(&pfd, 1, -1);
      while (n == -1 && errno == EINTR);

      if (n == -1 || (pfd.revents & ~POLLOUT) != 0) {
        errno = EIO;
        nsent = -1;
        goto out;
      }
    }

    offset += nread;
    nsent += nread;
  }

out:
  if (nsent != -1)
    req->off = offset;

  return nsent;
}