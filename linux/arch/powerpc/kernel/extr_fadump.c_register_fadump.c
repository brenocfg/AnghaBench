#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long fadumphdr_addr; TYPE_1__* ops; int /*<<< orphan*/  reserve_dump_area_size; } ;
struct TYPE_4__ {int (* fadump_register ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 void* __va (unsigned long) ; 
 int /*<<< orphan*/  fadump_create_elfcore_headers (void*) ; 
 int fadump_setup_crash_memory_ranges () ; 
 TYPE_2__ fw_dump ; 
 unsigned long init_fadump_header (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int register_fadump(void)
{
	unsigned long addr;
	void *vaddr;
	int ret;

	/*
	 * If no memory is reserved then we can not register for firmware-
	 * assisted dump.
	 */
	if (!fw_dump.reserve_dump_area_size)
		return -ENODEV;

	ret = fadump_setup_crash_memory_ranges();
	if (ret)
		return ret;

	addr = fw_dump.fadumphdr_addr;

	/* Initialize fadump crash info header. */
	addr = init_fadump_header(addr);
	vaddr = __va(addr);

	pr_debug("Creating ELF core headers at %#016lx\n", addr);
	fadump_create_elfcore_headers(vaddr);

	/* register the future kernel dump with firmware. */
	pr_debug("Registering for firmware-assisted kernel dump...\n");
	return fw_dump.ops->fadump_register(&fw_dump);
}