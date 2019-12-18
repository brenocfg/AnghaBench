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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int chdir (char*) ; 
 int close (int) ; 
 int dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,...) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lesser_daemon(void)
{
	int error, fd;

	error = chdir("/");
	if (error != 0)
		log_warn("chdir");

	fd = open(_PATH_DEVNULL, O_RDWR, 0);
	if (fd < 0) {
		log_warn("cannot open %s", _PATH_DEVNULL);
		return;
	}

	error = dup2(fd, STDIN_FILENO);
	if (error != 0)
		log_warn("dup2");

	error = close(fd);
	if (error != 0) {
		/* Bloody hell. */
		log_warn("close");
	}
}