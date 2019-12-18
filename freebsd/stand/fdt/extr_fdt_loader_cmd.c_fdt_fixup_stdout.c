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
struct fdt_property {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (char**,int) ; 
 struct fdt_property* fdt_get_property (int /*<<< orphan*/ ,int,char*,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fdt_setprop (int /*<<< orphan*/ ,int,char*,char***,int) ; 
 int /*<<< orphan*/  fdtp ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void
fdt_fixup_stdout(const char *str)
{
	char *ptr;
	int len, no, sero;
	const struct fdt_property *prop;
	char *tmp[10];

	ptr = (char *)str + strlen(str) - 1;
	while (ptr > str && isdigit(*(str - 1)))
		str--;

	if (ptr == str)
		return;

	no = fdt_path_offset(fdtp, "/chosen");
	if (no < 0)
		return;

	prop = fdt_get_property(fdtp, no, "stdout", &len);

	/* If /chosen/stdout does not extist, create it */
	if (prop == NULL || (prop != NULL && len == 0)) {

		bzero(tmp, 10 * sizeof(char));
		strcpy((char *)&tmp, "serial");
		if (strlen(ptr) > 3)
			/* Serial number too long */
			return;

		strncpy((char *)tmp + 6, ptr, 3);
		sero = fdt_path_offset(fdtp, (const char *)tmp);
		if (sero < 0)
			/*
			 * If serial device we're trying to assign
			 * stdout to doesn't exist in DT -- return.
			 */
			return;

		fdt_setprop(fdtp, no, "stdout", &tmp,
		    strlen((char *)&tmp) + 1);
		fdt_setprop(fdtp, no, "stdin", &tmp,
		    strlen((char *)&tmp) + 1);
	}
}