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
 int /*<<< orphan*/  DIOCSTARTALTQ ; 
 int /*<<< orphan*/  DIOCSTOPALTQ ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

void
altq_set_enabled(int enabled)
{
	int pffd;

	pffd = open("/dev/pf", O_RDWR);
	if (pffd == -1)
		err(EX_UNAVAILABLE,
		    "altq support opening pf(4) control device");
	if (enabled) {
		if (ioctl(pffd, DIOCSTARTALTQ) != 0 && errno != EEXIST)
			err(EX_UNAVAILABLE, "enabling altq");
	} else {
		if (ioctl(pffd, DIOCSTOPALTQ) != 0 && errno != ENOENT)
			err(EX_UNAVAILABLE, "disabling altq");
	}
	close(pffd);
}