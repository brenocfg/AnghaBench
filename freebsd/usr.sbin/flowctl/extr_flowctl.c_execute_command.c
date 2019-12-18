#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* cmd_func ) (int,char**) ;int /*<<< orphan*/ * cmd_name; } ;

/* Variables and functions */
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 

__attribute__((used)) static void
execute_command(int argc, char **argv)
{
	int cindex = -1;
	int i;

	if (!argc)
		help();
	for (i = 0; cmds[i].cmd_name != NULL; i++)
		if (!strncmp(argv[0], cmds[i].cmd_name, strlen(argv[0]))) {
			if (cindex != -1)
				errx(1, "ambiguous command: %s", argv[0]);
			cindex = i;
		}
	if (cindex == -1)
		errx(1, "bad command: %s", argv[0]);
	argc--;
	argv++;
	(*cmds[cindex].cmd_func)(argc, argv);
}