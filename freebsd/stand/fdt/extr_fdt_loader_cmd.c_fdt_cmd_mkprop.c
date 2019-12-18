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
 scalar_t__ fdt_extract_nameloc (char**,char**,int*) ; 
 scalar_t__ fdt_merge_strings (int,char**,int,char**) ; 
 scalar_t__ fdt_modprop (int,char*,char*,int) ; 

__attribute__((used)) static int
fdt_cmd_mkprop(int argc, char *argv[])
{
	int o;
	char *path, *propname, *value;

	path = (argc > 2) ? argv[2] : NULL;

	value = NULL;

	if (argc > 3) {
		/* Merge property value strings into one */
		if (fdt_merge_strings(argc, argv, 3, &value) != 0)
			return (CMD_ERROR);
	} else
		value = NULL;

	if (fdt_extract_nameloc(&path, &propname, &o) != 0)
		return (CMD_ERROR);

	if (fdt_modprop(o, propname, value, 1))
		return (CMD_ERROR);

	return (CMD_OK);
}