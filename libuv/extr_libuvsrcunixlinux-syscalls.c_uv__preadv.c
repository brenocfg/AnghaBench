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
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

ssize_t uv__preadv(int fd, const struct iovec *iov, int iovcnt, int64_t offset) {
#if defined(__NR_preadv)
  return syscall(__NR_preadv, fd, iov, iovcnt, (long)offset, (long)(offset >> 32));
#else
  return errno = ENOSYS, -1;
#endif
}