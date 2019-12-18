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
 int /*<<< orphan*/  free (char*) ; 
 char* generate_varrun_pidfile (char*) ; 
 int pidfile (char*) ; 

__attribute__((used)) static void
helper_mix(const char *unused_cookie)
{
	char *default_path;
	char *custom_path;

	default_path = generate_varrun_pidfile(NULL);
	custom_path = generate_varrun_pidfile("custom-basename");

	if (pidfile(NULL) == -1)
		errx(EXIT_FAILURE, "Failed to create default pidfile");
	check_pidfile(default_path);

	if (pidfile("./second.pid") == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile 'second.pid'");
	ensure_deleted(default_path);
	check_pidfile("./second.pid");

	if (pidfile("custom-basename") == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile 'second.pid'");
	ensure_deleted(default_path);
	ensure_deleted("./second.pid");
	ensure_deleted("./custom-basename");
	check_pidfile(custom_path);

	free(custom_path);
	free(default_path);
	exit(EXIT_SUCCESS);
}