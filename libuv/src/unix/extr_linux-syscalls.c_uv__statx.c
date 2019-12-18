#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uv__statx {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  __NR_statx ; 
 int errno ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,int,unsigned int,struct uv__statx*) ; 

int uv__statx(int dirfd,
              const char* path,
              int flags,
              unsigned int mask,
              struct uv__statx* statxbuf) {
  /* __NR_statx make Android box killed by SIGSYS.
   * That looks like a seccomp2 sandbox filter rejecting the system call.
   */
#if defined(__NR_statx) && !defined(__ANDROID__)
  return syscall(__NR_statx, dirfd, path, flags, mask, statxbuf);
#else
  return errno = ENOSYS, -1;
#endif
}