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
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mingw_execv (char*,char* const*) ; 
 char* path_lookup (char const*,int /*<<< orphan*/ ) ; 

int mingw_execvp(const char *cmd, char *const *argv)
{
	char *prog = path_lookup(cmd, 0);

	if (prog) {
		mingw_execv(prog, argv);
		free(prog);
	} else
		errno = ENOENT;

	return -1;
}