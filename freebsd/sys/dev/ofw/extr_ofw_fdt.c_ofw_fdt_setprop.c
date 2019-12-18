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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ofw_t ;

/* Variables and functions */
 int fdt_phandle_offset (int /*<<< orphan*/ ) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,char const*,void const*,size_t) ; 
 scalar_t__ fdt_setprop_inplace (int /*<<< orphan*/ ,int,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  fdtp ; 

__attribute__((used)) static int
ofw_fdt_setprop(ofw_t ofw, phandle_t package, const char *propname,
    const void *buf, size_t len)
{
	int offset;

	offset = fdt_phandle_offset(package);
	if (offset < 0)
		return (-1);

	if (fdt_setprop_inplace(fdtp, offset, propname, buf, len) != 0)
		/* Try to add property, when setting value inplace failed */
		return (fdt_setprop(fdtp, offset, propname, buf, len));

	return (0);
}