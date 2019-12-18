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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fdt64_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fdt_add_mem_rsv (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_delprop (void*,int,char*) ; 
 void* fdt_getprop (void*,int,char*,int*) ; 
 int fdt_path_offset (void*,char*) ; 
 int /*<<< orphan*/  fdt_setprop (void*,int,char*,void const*,int) ; 

__attribute__((used)) static void
fdt_linux_fixups(void *fdtp)
{
	int offset, len;
	const void *prop;

	/*
	 * Remove /memory/available properties, which reflect long-gone OF
	 * state
	 */

	offset = fdt_path_offset(fdtp, "/memory@0");
	if (offset > 0)
		fdt_delprop(fdtp, offset, "available");

	/*
	 * Add reservations for OPAL and RTAS state if present
	 */

	offset = fdt_path_offset(fdtp, "/ibm,opal");
	if (offset > 0) {
		const uint64_t *base, *size;
		base = fdt_getprop(fdtp, offset, "opal-base-address",
		    &len);
		size = fdt_getprop(fdtp, offset, "opal-runtime-size",
		    &len);
		if (base != NULL && size != NULL)
			fdt_add_mem_rsv(fdtp, fdt64_to_cpu(*base),
			    fdt64_to_cpu(*size));
	}
	offset = fdt_path_offset(fdtp, "/rtas");
	if (offset > 0) {
		const uint32_t *base, *size;
		base = fdt_getprop(fdtp, offset, "linux,rtas-base", &len);
		size = fdt_getprop(fdtp, offset, "rtas-size", &len);
		if (base != NULL && size != NULL)
			fdt_add_mem_rsv(fdtp, fdt32_to_cpu(*base),
			    fdt32_to_cpu(*size));
	}

	/*
	 * Patch up /chosen nodes so that the stored handles mean something,
	 * where possible.
	 */
	offset = fdt_path_offset(fdtp, "/chosen");
	if (offset > 0) {
		fdt_delprop(fdtp, offset, "cpu"); /* This node not meaningful */

		offset = fdt_path_offset(fdtp, "/chosen");
		prop = fdt_getprop(fdtp, offset, "linux,stdout-package", &len);
		if (prop != NULL) {
			fdt_setprop(fdtp, offset, "stdout", prop, len);
			offset = fdt_path_offset(fdtp, "/chosen");
			fdt_setprop(fdtp, offset, "stdin", prop, len);
		}
	}
}