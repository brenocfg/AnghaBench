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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,...) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int daemonfd (int,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ log_perror ; 
 scalar_t__ no_daemon ; 
 int nullfd ; 
 int /*<<< orphan*/ * pidfile ; 
 int /*<<< orphan*/  pidfile_fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_write (int /*<<< orphan*/ *) ; 

void
go_daemon(void)
{
	static int state = 0;
	cap_rights_t rights;

	if (no_daemon || state)
		return;

	state = 1;

	/* Stop logging to stderr... */
	log_perror = 0;

	if (daemonfd(-1, nullfd) == -1)
		error("daemon");

	cap_rights_init(&rights);

	if (pidfile != NULL) {
		pidfile_write(pidfile);

		if (caph_rights_limit(pidfile_fileno(pidfile), &rights) < 0)
			error("can't limit pidfile descriptor: %m");
	}

	if (nullfd != -1) {
		close(nullfd);
		nullfd = -1;
	}

	if (caph_rights_limit(STDIN_FILENO, &rights) < 0)
		error("can't limit stdin: %m");
	cap_rights_init(&rights, CAP_WRITE);
	if (caph_rights_limit(STDOUT_FILENO, &rights) < 0)
		error("can't limit stdout: %m");
	if (caph_rights_limit(STDERR_FILENO, &rights) < 0)
		error("can't limit stderr: %m");
}