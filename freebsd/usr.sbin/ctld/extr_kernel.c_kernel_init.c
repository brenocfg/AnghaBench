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
 int /*<<< orphan*/  CTL_DEFAULT_DEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ ctl_fd ; 
 int errno ; 
 int kldload (char*) ; 
 int /*<<< orphan*/  log_err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int modfind (char*) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kernel_init(void)
{
	int retval, saved_errno;

	ctl_fd = open(CTL_DEFAULT_DEV, O_RDWR);
	if (ctl_fd < 0 && errno == ENOENT) {
		saved_errno = errno;
		retval = kldload("ctl");
		if (retval != -1)
			ctl_fd = open(CTL_DEFAULT_DEV, O_RDWR);
		else
			errno = saved_errno;
	}
	if (ctl_fd < 0)
		log_err(1, "failed to open %s", CTL_DEFAULT_DEV);
#ifdef	WANT_ISCSI
	else {
		saved_errno = errno;
		if (modfind("cfiscsi") == -1 && kldload("cfiscsi") == -1)
			log_warn("couldn't load cfiscsi");
		errno = saved_errno;
	}
#endif
}