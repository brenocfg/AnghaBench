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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int ENOSYS ; 
 int errno ; 

int uv__accept4(int fd, struct sockaddr* addr, socklen_t* addrlen, int flags) {
#if defined(__i386__)
  unsigned long args[4];
  int r;

  args[0] = (unsigned long) fd;
  args[1] = (unsigned long) addr;
  args[2] = (unsigned long) addrlen;
  args[3] = (unsigned long) flags;

  r = syscall(__NR_socketcall, 18 /* SYS_ACCEPT4 */, args);

  /* socketcall() raises EINVAL when SYS_ACCEPT4 is not supported but so does
   * a bad flags argument. Try to distinguish between the two cases.
   */
  if (r == -1)
    if (errno == EINVAL)
      if ((flags & ~(UV__SOCK_CLOEXEC|UV__SOCK_NONBLOCK)) == 0)
        errno = ENOSYS;

  return r;
#elif defined(__NR_accept4)
  return syscall(__NR_accept4, fd, addr, addrlen, flags);
#else
  return errno = ENOSYS, -1;
#endif
}