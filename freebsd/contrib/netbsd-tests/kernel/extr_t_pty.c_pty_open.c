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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  condition (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int grantpt (int) ; 
 int posix_openpt (int /*<<< orphan*/ ) ; 
 int unlockpt (int) ; 

__attribute__((used)) static int
pty_open(void)
{
	int	fd;

	if ((fd = posix_openpt(O_RDWR)) == -1)
		err(EXIT_FAILURE, "Couldn't pty(4) device");
	condition(fd);
	if (grantpt(fd) == -1)
		err(EXIT_FAILURE,
		    "Couldn't grant permissions on tty(4) device");


	condition(fd);

	if (unlockpt(fd) == -1)
		err(EXIT_FAILURE, "unlockpt()");

	return fd;
}