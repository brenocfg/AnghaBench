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
 int /*<<< orphan*/  add_node_to_fdt (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_create_empty_tree (void*,size_t) ; 
 int /*<<< orphan*/  fdt_linux_fixups (void*) ; 
 int /*<<< orphan*/  fdt_load_dtb_addr (void*) ; 
 int /*<<< orphan*/  fdt_pack (void*) ; 
 int /*<<< orphan*/  fdt_path_offset (void*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 

int
fdt_platform_load_dtb(void)
{
	void *buffer;
	size_t buflen = 409600;

	buffer = malloc(buflen);
	fdt_create_empty_tree(buffer, buflen);
	add_node_to_fdt(buffer, "/proc/device-tree",
	    fdt_path_offset(buffer, "/"));
	fdt_linux_fixups(buffer);

	fdt_pack(buffer);

	fdt_load_dtb_addr(buffer);
	free(buffer);
	
	return (0);
}