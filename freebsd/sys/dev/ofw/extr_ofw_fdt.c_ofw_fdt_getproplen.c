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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ofw_t ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdt_get_name (int /*<<< orphan*/ ,int,int*) ; 
 void* fdt_getprop (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_num_mem_rsv (int /*<<< orphan*/ ) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int fdt_phandle_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtp ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static ssize_t
ofw_fdt_getproplen(ofw_t ofw, phandle_t package, const char *propname)
{
	const void *prop;
	int offset, len;

	offset = fdt_phandle_offset(package);
	if (offset < 0)
		return (-1);

	len = -1;
	prop = fdt_getprop(fdtp, offset, propname, &len);

	if (prop == NULL && strcmp(propname, "name") == 0) {
		/* Emulate the 'name' property */
		fdt_get_name(fdtp, offset, &len);
		return (len + 1);
	}

	if (prop == NULL && offset == fdt_path_offset(fdtp, "/chosen")) {
		if (strcmp(propname, "fdtbootcpu") == 0)
			return (sizeof(cell_t));
		if (strcmp(propname, "fdtmemreserv") == 0)
			return (sizeof(uint64_t)*2*fdt_num_mem_rsv(fdtp));
	}

	if (prop == NULL)
		return (-1);

	return (len);
}