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
struct our_mmsghdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  __NR_sendmmsg ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int sendmmsg_supported ; 
 int /*<<< orphan*/  stderr ; 
 int syscall (int /*<<< orphan*/ ,int,struct our_mmsghdr*,unsigned int,unsigned int) ; 
 scalar_t__ verbosity ; 

int our_sendmmsg (int sockfd, struct our_mmsghdr *msgvec, unsigned int vlen,
	     unsigned int flags) {
  if (sendmmsg_supported > 0) {
    return syscall (__NR_sendmmsg, sockfd, msgvec, vlen, flags);
  } else if (sendmmsg_supported < 0) {
    errno = ENOSYS;
    return -1;
  }
  int res = syscall (__NR_sendmmsg, sockfd, msgvec, vlen, flags);
  if (res < 0 && errno == ENOSYS) {
    if (verbosity > 0) {
      fprintf (stderr, "warning: sendmmsg() not supported, falling back to sendmsg()\n");
      errno = ENOSYS;
    }
    sendmmsg_supported = -1;
  } else {
    sendmmsg_supported = 1;
  }
  return res;
}