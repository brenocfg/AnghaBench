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

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (int) ; 
 int dup (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tree_dup(int fd)
{
	int new_fd;
#ifdef F_DUPFD_CLOEXEC
	static volatile int can_dupfd_cloexec = 1;

	if (can_dupfd_cloexec) {
		new_fd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
		if (new_fd != -1)
			return (new_fd);
		/* Linux 2.6.18 - 2.6.23 declare F_DUPFD_CLOEXEC,
		 * but it cannot be used. So we have to try dup(). */
		/* We won't try F_DUPFD_CLOEXEC. */
		can_dupfd_cloexec = 0;
	}
#endif /* F_DUPFD_CLOEXEC */
	new_fd = dup(fd);
	__archive_ensure_cloexec_flag(new_fd);
	return (new_fd);
}