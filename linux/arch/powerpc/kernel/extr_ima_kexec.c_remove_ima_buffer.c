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
 int delete_fdt_mem_rsv (void*,unsigned long,size_t) ; 
 int do_get_kexec_buffer (void const*,int,unsigned long*,size_t*) ; 
 int /*<<< orphan*/  fdt_delprop (void*,int,char*) ; 
 void* fdt_getprop (void*,int,char*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void remove_ima_buffer(void *fdt, int chosen_node)
{
	int ret, len;
	unsigned long addr;
	size_t size;
	const void *prop;

	prop = fdt_getprop(fdt, chosen_node, "linux,ima-kexec-buffer", &len);
	if (!prop)
		return;

	ret = do_get_kexec_buffer(prop, len, &addr, &size);
	fdt_delprop(fdt, chosen_node, "linux,ima-kexec-buffer");
	if (ret)
		return;

	ret = delete_fdt_mem_rsv(fdt, addr, size);
	if (!ret)
		pr_debug("Removed old IMA buffer reservation.\n");
}