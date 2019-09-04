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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int RUN_COMMAND_NO_STDIN ; 
 int RUN_GIT_CMD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* git_pathdup (char*) ; 
 scalar_t__ run_command_v_opt (char const**,int) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void dissociate_from_references(void)
{
	static const char* argv[] = { "repack", "-a", "-d", NULL };
	char *alternates = git_pathdup("objects/info/alternates");

	if (!access(alternates, F_OK)) {
		if (run_command_v_opt(argv, RUN_GIT_CMD|RUN_COMMAND_NO_STDIN))
			die(_("cannot repack to clean up"));
		if (unlink(alternates) && errno != ENOENT)
			die_errno(_("cannot unlink temporary alternates file"));
	}
	free(alternates);
}