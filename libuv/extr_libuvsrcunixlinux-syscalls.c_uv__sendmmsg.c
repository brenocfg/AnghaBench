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
struct uv__mmsghdr {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int errno ; 

int uv__sendmmsg(int fd,
                 struct uv__mmsghdr* mmsg,
                 unsigned int vlen,
                 unsigned int flags) {
#if defined(__NR_sendmmsg)
  return syscall(__NR_sendmmsg, fd, mmsg, vlen, flags);
#else
  return errno = ENOSYS, -1;
#endif
}