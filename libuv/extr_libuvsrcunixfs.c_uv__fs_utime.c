#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int atime; int mtime; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int uint64_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  utimensat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uv__fs_utime(uv_fs_t* req) {
#if defined(__linux__)                                                         \
    || defined(_AIX71)                                                         \
    || defined(__sun)
  /* utimesat() has nanosecond resolution but we stick to microseconds
   * for the sake of consistency with other platforms.
   */
  struct timespec ts[2];
  ts[0].tv_sec  = req->atime;
  ts[0].tv_nsec = (uint64_t)(req->atime * 1000000) % 1000000 * 1000;
  ts[1].tv_sec  = req->mtime;
  ts[1].tv_nsec = (uint64_t)(req->mtime * 1000000) % 1000000 * 1000;
  return utimensat(AT_FDCWD, req->path, ts, 0);
#elif defined(__APPLE__)                                                      \
    || defined(__DragonFly__)                                                 \
    || defined(__FreeBSD__)                                                   \
    || defined(__FreeBSD_kernel__)                                            \
    || defined(__NetBSD__)                                                    \
    || defined(__OpenBSD__)
  struct timeval tv[2];
  tv[0].tv_sec  = req->atime;
  tv[0].tv_usec = (uint64_t)(req->atime * 1000000) % 1000000;
  tv[1].tv_sec  = req->mtime;
  tv[1].tv_usec = (uint64_t)(req->mtime * 1000000) % 1000000;
  return utimes(req->path, tv);
#elif defined(_AIX)                                                           \
    && !defined(_AIX71)
  struct utimbuf buf;
  buf.actime = req->atime;
  buf.modtime = req->mtime;
  return utime(req->path, &buf);
#elif defined(__MVS__)
  attrib_t atr;
  memset(&atr, 0, sizeof(atr));
  atr.att_mtimechg = 1;
  atr.att_atimechg = 1;
  atr.att_mtime = req->mtime;
  atr.att_atime = req->atime;
  return __lchattr((char*) req->path, &atr, sizeof(atr));
#else
  errno = ENOSYS;
  return -1;
#endif
}