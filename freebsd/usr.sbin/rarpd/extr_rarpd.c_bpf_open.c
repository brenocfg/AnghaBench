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
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pidfile_fh ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bpf_open(void)
{
	int fd;
	int n = 0;
	char device[sizeof "/dev/bpf000"];

	/*
	 * Go through all the minors and find one that isn't in use.
	 */
	do {
		(void)sprintf(device, "/dev/bpf%d", n++);
		fd = open(device, O_RDWR);
	} while ((fd == -1) && (errno == EBUSY));

	if (fd == -1) {
		logmsg(LOG_ERR, "%s: %m", device);
		pidfile_remove(pidfile_fh);
		exit(1);
	}
	return fd;
}