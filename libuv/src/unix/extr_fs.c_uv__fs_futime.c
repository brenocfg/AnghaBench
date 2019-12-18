#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int atime; int mtime; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int uint64_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int ssize_t ;
struct TYPE_7__ {int att_mtimechg; int att_atimechg; int att_mtime; int att_atime; } ;
typedef  TYPE_2__ attrib_t ;
typedef  int /*<<< orphan*/  atr ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int __fchattr (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  errno ; 
 int futimens (int /*<<< orphan*/ ,struct timespec*) ; 
 int futimes (int /*<<< orphan*/ ,struct timeval*) ; 
 int futimesat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int utimensat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timespec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uv__fs_futime(uv_fs_t* req) {
#if defined(__linux__)                                                        \
    || defined(_AIX71)                                                        \
    || defined(__HAIKU__)
  /* utimesat() has nanosecond resolution but we stick to microseconds
   * for the sake of consistency with other platforms.
   */
  struct timespec ts[2];
  ts[0].tv_sec  = req->atime;
  ts[0].tv_nsec = (uint64_t)(req->atime * 1000000) % 1000000 * 1000;
  ts[1].tv_sec  = req->mtime;
  ts[1].tv_nsec = (uint64_t)(req->mtime * 1000000) % 1000000 * 1000;
#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
  return utimensat(req->file, NULL, ts, 0);
#else
  return futimens(req->file, ts);
#endif
#elif defined(__APPLE__)                                                      \
    || defined(__DragonFly__)                                                 \
    || defined(__FreeBSD__)                                                   \
    || defined(__FreeBSD_kernel__)                                            \
    || defined(__NetBSD__)                                                    \
    || defined(__OpenBSD__)                                                   \
    || defined(__sun)
  struct timeval tv[2];
  tv[0].tv_sec  = req->atime;
  tv[0].tv_usec = (uint64_t)(req->atime * 1000000) % 1000000;
  tv[1].tv_sec  = req->mtime;
  tv[1].tv_usec = (uint64_t)(req->mtime * 1000000) % 1000000;
# if defined(__sun)
  return futimesat(req->file, NULL, tv);
# else
  return futimes(req->file, tv);
# endif
#elif defined(__MVS__)
  attrib_t atr;
  memset(&atr, 0, sizeof(atr));
  atr.att_mtimechg = 1;
  atr.att_atimechg = 1;
  atr.att_mtime = req->mtime;
  atr.att_atime = req->atime;
  return __fchattr(req->file, &atr, sizeof(atr));
#else
  errno = ENOSYS;
  return -1;
#endif
}