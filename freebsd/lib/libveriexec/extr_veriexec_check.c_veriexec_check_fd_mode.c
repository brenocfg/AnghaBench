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
 int EINVAL ; 
#define  ENOSYS 128 
 int /*<<< orphan*/  MAC_VERIEXEC_CHECK_FD_SYSCALL ; 
 int /*<<< orphan*/  MAC_VERIEXEC_NAME ; 
 int check_fd_mode (int,unsigned int) ; 
 int errno ; 
 int mac_syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
veriexec_check_fd_mode(int fd, unsigned int mask)
{
	int error;

	if (fd < 0) {
		errno = EINVAL;
		return -1;
	}

	error = mac_syscall(MAC_VERIEXEC_NAME, MAC_VERIEXEC_CHECK_FD_SYSCALL,
	    (void *)(intptr_t)fd);
	if (error == -1) {
		switch (errno) {
		case ENOSYS:	/* veriexec not loaded */
			error = 0;	/* ignore */
			break;
		}
	}
	if (mask && error == 0)
	    error = check_fd_mode(fd, mask);

	return (error);
}