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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  check_pidfile (char*) ; 
 int /*<<< orphan*/  ensure_deleted (char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int pidfile (char*) ; 

__attribute__((used)) static void
helper_change_paths(const char *unused_cookie)
{

	if (pidfile("./var/run/first.pid") == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile "
		    "'./var/run/first.pid'");
	check_pidfile("./var/run/first.pid");

	if (pidfile("./second.pid") == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile 'second.pid'");
	ensure_deleted("./var/run/first.pid");
	check_pidfile("./second.pid");

	exit(EXIT_SUCCESS);
}