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
typedef  int (* cmdf_t ) (int,char**) ;
struct TYPE_2__ {int (* handler ) (int,char**) ;int flags; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_REQUIRES_BLOB ; 
 char* command_errmsg ; 
 TYPE_1__* commands ; 
 scalar_t__ fdt_fixup () ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int stub1 (int,char**) ; 

int
command_fdt_internal(int argc, char *argv[])
{
	cmdf_t *cmdh;
	int flags;
	int i, err;

	if (argc < 2) {
		command_errmsg = "usage is 'fdt <command> [<args>]";
		return (CMD_ERROR);
	}

	/*
	 * Validate fdt <command>.
	 */
	i = 0;
	cmdh = NULL;
	while (!(commands[i].name == NULL)) {
		if (strcmp(argv[1], commands[i].name) == 0) {
			/* found it */
			cmdh = commands[i].handler;
			flags = commands[i].flags;
			break;
		}
		i++;
	}
	if (cmdh == NULL) {
		command_errmsg = "unknown command";
		return (CMD_ERROR);
	}

	if (flags & CMD_REQUIRES_BLOB) {
		/*
		 * Check if uboot env vars were parsed already. If not, do it now.
		 */
		if (fdt_fixup() == 0)
			return (CMD_ERROR);
	}

	/*
	 * Call command handler.
	 */
	err = (*cmdh)(argc, argv);

	return (err);
}