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
 int /*<<< orphan*/  O_RDWR ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setsid () ; 

__attribute__((used)) static void
stdnull(void)
{
	int fd;

	fd = open(_PATH_DEVNULL, O_RDWR);
	if (fd == -1)
		errx(1, "Unable to open %s", _PATH_DEVNULL);

	if (setsid() == -1)
		errx(1, "Unable to detach from session");

	if (dup2(fd, STDIN_FILENO) == -1)
		errx(1, "Unable to cover stdin");
	if (dup2(fd, STDOUT_FILENO) == -1)
		errx(1, "Unable to cover stdout");
	if (dup2(fd, STDERR_FILENO) == -1)
		errx(1, "Unable to cover stderr");

	if (fd > STDERR_FILENO)
		close(fd);
}