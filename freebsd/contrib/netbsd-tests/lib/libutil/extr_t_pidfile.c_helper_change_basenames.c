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
helper_change_basenames(const char *unused_cookie)
{
	char *default_path;
	char *custom_path;

	default_path = generate_varrun_pidfile(NULL);
	if (pidfile(NULL) == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile with default "
		    "basename");
	check_pidfile(default_path);
	if (pidfile(NULL) == -1)
		errx(EXIT_FAILURE, "Failed to recreate pidfile with default "
		    "basename");
	check_pidfile(default_path);

	custom_path = generate_varrun_pidfile("custom-basename");
	if (pidfile("custom-basename") == -1)
		errx(EXIT_FAILURE, "Failed to create pidfile with custom "
		    "basename");
	ensure_deleted(default_path);
	check_pidfile(custom_path);
	if (pidfile("custom-basename") == -1)
		errx(EXIT_FAILURE, "Failed to recreate pidfile with custom "
		    "basename");
	check_pidfile(custom_path);

	free(custom_path);
	free(default_path);
	exit(EXIT_SUCCESS);
}