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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fdt_property {int dummy; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  command_errbuf ; 
 struct fdt_property* fdt_get_property (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ **,int) ; 
 int fdt_setprop_string (int /*<<< orphan*/ ,int,char*,void*) ; 
 int fdt_strtovect (char const*,void*,int,int) ; 
 int /*<<< orphan*/  fdtp ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
fdt_modprop(int nodeoff, char *propname, void *value, char mode)
{
	uint32_t cells[100];
	const char *buf;
	int len, rv;
	const struct fdt_property *p;

	p = fdt_get_property(fdtp, nodeoff, propname, NULL);

	if (p != NULL) {
		if (mode == 1) {
			 /* Adding inexistant value in mode 1 is forbidden */
			sprintf(command_errbuf, "property already exists!");
			return (CMD_ERROR);
		}
	} else if (mode == 0) {
		sprintf(command_errbuf, "property does not exist!");
		return (CMD_ERROR);
	}
	rv = 0;
	buf = value;

	switch (*buf) {
	case '&':
		/* phandles */
		break;
	case '<':
		/* Data cells */
		len = fdt_strtovect(buf, (void *)&cells, 100,
		    sizeof(uint32_t));

		rv = fdt_setprop(fdtp, nodeoff, propname, &cells,
		    len * sizeof(uint32_t));
		break;
	case '[':
		/* Data bytes */
		len = fdt_strtovect(buf, (void *)&cells, 100,
		    sizeof(uint8_t));

		rv = fdt_setprop(fdtp, nodeoff, propname, &cells,
		    len * sizeof(uint8_t));
		break;
	case '"':
	default:
		/* Default -- string */
		rv = fdt_setprop_string(fdtp, nodeoff, propname, value);
		break;
	}

	if (rv != 0) {
		if (rv == -FDT_ERR_NOSPACE)
			sprintf(command_errbuf,
			    "Device tree blob is too small!\n");
		else
			sprintf(command_errbuf,
			    "Could not add/modify property!\n");
	}
	return (rv);
}