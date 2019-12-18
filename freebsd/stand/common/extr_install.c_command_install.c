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
 int CMD_ERROR ; 
 char* command_errmsg ; 
 int install (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static int
command_install(int argc, char *argv[])
{
	int argidx;

	unsetenv("install_format");

	argidx = 1;
	while (1) {
		if (argc == argidx) {
			command_errmsg =
			    "usage: install [--format] <URL>";
			return (CMD_ERROR);
		}
		if (!strcmp(argv[argidx], "--format")) {
			setenv("install_format", "yes", 1);
			argidx++;
			continue;
		}
		break;
	}

	return (install(argv[argidx]));
}