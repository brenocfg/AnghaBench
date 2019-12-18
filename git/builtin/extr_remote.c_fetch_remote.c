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
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int fetch_remote(const char *name)
{
	const char *argv[] = { "fetch", name, NULL, NULL };
	if (verbose) {
		argv[1] = "-v";
		argv[2] = name;
	}
	printf_ln(_("Updating %s"), name);
	if (run_command_v_opt(argv, RUN_GIT_CMD))
		return error(_("Could not fetch %s"), name);
	return 0;
}