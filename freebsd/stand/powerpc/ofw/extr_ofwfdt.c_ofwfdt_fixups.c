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
typedef  int uint32_t ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  node ;
typedef  int /*<<< orphan*/  len ;
typedef  scalar_t__ ihandle_t ;
typedef  int /*<<< orphan*/  cell_t ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */
 int /*<<< orphan*/  OF_call_method (char*,scalar_t__,int,int,int /*<<< orphan*/ ,int*) ; 
 void* OF_claim (int /*<<< orphan*/ ,int,int) ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getprop (int,char*,int*,int) ; 
 scalar_t__ OF_hasprop (int,char*) ; 
 int OF_instance_to_package (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_open (char*) ; 
 int /*<<< orphan*/  OF_package_to_path (int,char*,int) ; 
 int cpu_to_fdt32 (int) ; 
 int /*<<< orphan*/  fdt32_to_cpu (int const) ; 
 int /*<<< orphan*/  fdt_add_mem_rsv (void*,int,int) ; 
 int /*<<< orphan*/  fdt_delprop (void*,int,char*) ; 
 int* fdt_getprop (void*,int,char const*,int*) ; 
 int fdt_path_offset (void*,char*) ; 
 int /*<<< orphan*/  fdt_setprop (void*,int,char const*,int*,int) ; 

__attribute__((used)) static void
ofwfdt_fixups(void *fdtp)
{
	int offset, len, i;
	phandle_t node;
	ihandle_t rtas;
	const void *prop;

	/*
	 * Instantiate and add reservations for RTAS state if present
	 */

	offset = fdt_path_offset(fdtp, "/rtas");
	if (offset > 0) {
		uint32_t base;
		void *rtasmem;
		char path[255];

		node = OF_finddevice("/rtas");
		OF_package_to_path(node, path, sizeof(path));
		OF_getprop(node, "rtas-size", &len, sizeof(len));

		/* Allocate memory */
		rtasmem = OF_claim(0, len, 4096);

		/* Instantiate RTAS */
		rtas = OF_open(path);
		base = 0;
		OF_call_method("instantiate-rtas", rtas, 1, 1, (cell_t)rtas,
		    &base);

		/* Store info to FDT using Linux convention */
		base = cpu_to_fdt32(base);
		fdt_setprop(fdtp, offset, "linux,rtas-entry", &base,
		    sizeof(base));
		base = cpu_to_fdt32((uint32_t)rtasmem);
		offset = fdt_path_offset(fdtp, "/rtas");
		fdt_setprop(fdtp, offset, "linux,rtas-base", &base,
		    sizeof(base));

		/* Mark RTAS private data area reserved */
		fdt_add_mem_rsv(fdtp, base, len);
	} else {
		/*
		 * Remove /memory/available properties, which reflect long-gone
		 * OF state. Note that this doesn't work if we need RTAS still,
		 * since that's part of the firmware.
		 */
		offset = fdt_path_offset(fdtp, "/memory@0");
		if (offset > 0)
			fdt_delprop(fdtp, offset, "available");
	}

	
	/*
	 * Convert stored ihandles under /chosen to xref phandles
	 */
	offset = fdt_path_offset(fdtp, "/chosen");
	if (offset > 0) {
		const char *chosenprops[] = {"stdout", "stdin", "mmu", "cpu",
		    NULL};
		const uint32_t *ihand;
		for (i = 0; chosenprops[i] != NULL; i++) {
			ihand = fdt_getprop(fdtp, offset, chosenprops[i], &len);
			if (ihand != NULL && len == sizeof(*ihand)) {
				node = OF_instance_to_package(
				    fdt32_to_cpu(*ihand));
				if (OF_hasprop(node, "phandle"))
					OF_getprop(node, "phandle", &node,
					    sizeof(node));
				else if (OF_hasprop(node, "linux,phandle"))
					OF_getprop(node, "linux,phandle", &node,
					    sizeof(node));
				else if (OF_hasprop(node, "ibm,phandle"))
					OF_getprop(node, "ibm,phandle", &node,
					    sizeof(node));
				node = cpu_to_fdt32(node);
				fdt_setprop(fdtp, offset, chosenprops[i], &node,
				    sizeof(node));
			}

			/* Refind node in case it moved */
			offset = fdt_path_offset(fdtp, "/chosen");
		}
	}
}