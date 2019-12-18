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
 int FDT_ERR_BADVERSION ; 
 struct fdt_property const* fdt_get_property_by_offset_ (void const*,int,int*) ; 
 int fdt_version (void const*) ; 

const struct fdt_property *fdt_get_property_by_offset(const void *fdt,
						      int offset,
						      int *lenp)
{
	/* Prior to version 16, properties may need realignment
	 * and this API does not work. fdt_getprop_*() will, however. */

	if (fdt_version(fdt) < 0x10) {
		if (lenp)
			*lenp = -FDT_ERR_BADVERSION;
		return NULL;
	}

	return fdt_get_property_by_offset_(fdt, offset, lenp);
}