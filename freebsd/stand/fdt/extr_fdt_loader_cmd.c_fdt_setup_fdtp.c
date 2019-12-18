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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct preloaded_file {char* f_name; int /*<<< orphan*/  f_addr; } ;

/* Variables and functions */
 char* command_errmsg ; 
 int /*<<< orphan*/  debugf (char*) ; 
 int /*<<< orphan*/  fdt_find_static_dtb () ; 
 scalar_t__ fdt_load_dtb (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_load_dtb_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ fdt_platform_load_dtb () ; 
 int /*<<< orphan*/  fdt_platform_load_overlays () ; 
 int /*<<< orphan*/ * fdt_to_load ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
fdt_setup_fdtp()
{
	struct preloaded_file *bfp;
	vm_offset_t va;
	
	debugf("fdt_setup_fdtp()\n");

	/* If we already loaded a file, use it. */
	if ((bfp = file_findfile(NULL, "dtb")) != NULL) {
		if (fdt_load_dtb(bfp->f_addr) == 0) {
			printf("Using DTB from loaded file '%s'.\n", 
			    bfp->f_name);
			fdt_platform_load_overlays();
			return (0);
		}
	}

	/* If we were given the address of a valid blob in memory, use it. */
	if (fdt_to_load != NULL) {
		if (fdt_load_dtb_addr(fdt_to_load) == 0) {
			printf("Using DTB from memory address %p.\n",
			    fdt_to_load);
			fdt_platform_load_overlays();
			return (0);
		}
	}

	if (fdt_platform_load_dtb() == 0) {
		fdt_platform_load_overlays();
		return (0);
	}

	/* If there is a dtb compiled into the kernel, use it. */
	if ((va = fdt_find_static_dtb()) != 0) {
		if (fdt_load_dtb(va) == 0) {
			printf("Using DTB compiled into kernel.\n");
			return (0);
		}
	}
	
	command_errmsg = "No device tree blob found!\n";
	return (1);
}