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
 int CMD_OK ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  command_errbuf ; 
 int fdt_add_subnode (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ fdt_extract_nameloc (char**,char**,int*) ; 
 int /*<<< orphan*/  fdtp ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
fdt_cmd_mknode(int argc, char *argv[])
{
	int o, rv;
	char *path = NULL, *nodename = NULL;

	if (argc > 2)
		path = argv[2];
	else {
		sprintf(command_errbuf, "no node name specified");
		return (CMD_ERROR);
	}

	if (fdt_extract_nameloc(&path, &nodename, &o) != 0)
		return (CMD_ERROR);

	rv = fdt_add_subnode(fdtp, o, nodename);

	if (rv < 0) {
		if (rv == -FDT_ERR_NOSPACE)
			sprintf(command_errbuf,
			    "Device tree blob is too small!\n");
		else
			sprintf(command_errbuf,
			    "Could not add node!\n");
		return (CMD_ERROR);
	}
	return (CMD_OK);
}