#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct opal_fadump_mem_struct {int region_cnt; int registered_regions; TYPE_1__* rgn; } ;
struct fw_dump {unsigned long* boot_mem_addr; unsigned long* boot_mem_sz; int boot_mem_regs_cnt; scalar_t__ boot_memory_size; scalar_t__ boot_mem_top; int /*<<< orphan*/  reserve_dump_area_start; int /*<<< orphan*/  dump_active; } ;
struct TYPE_2__ {unsigned long src; unsigned long size; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  opal_fadump_update_config (struct fw_dump*,struct opal_fadump_mem_struct const*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static void opal_fadump_get_config(struct fw_dump *fadump_conf,
				   const struct opal_fadump_mem_struct *fdm)
{
	unsigned long base, size, last_end, hole_size;
	int i;

	if (!fadump_conf->dump_active)
		return;

	last_end = 0;
	hole_size = 0;
	fadump_conf->boot_memory_size = 0;

	pr_debug("Boot memory regions:\n");
	for (i = 0; i < fdm->region_cnt; i++) {
		base = fdm->rgn[i].src;
		size = fdm->rgn[i].size;
		pr_debug("\t[%03d] base: 0x%lx, size: 0x%lx\n", i, base, size);

		fadump_conf->boot_mem_addr[i] = base;
		fadump_conf->boot_mem_sz[i] = size;
		fadump_conf->boot_memory_size += size;
		hole_size += (base - last_end);

		last_end = base + size;
	}

	/*
	 * Start address of reserve dump area (permanent reservation) for
	 * re-registering FADump after dump capture.
	 */
	fadump_conf->reserve_dump_area_start = fdm->rgn[0].dest;

	/*
	 * Rarely, but it can so happen that system crashes before all
	 * boot memory regions are registered for MPIPL. In such
	 * cases, warn that the vmcore may not be accurate and proceed
	 * anyway as that is the best bet considering free pages, cache
	 * pages, user pages, etc are usually filtered out.
	 *
	 * Hope the memory that could not be preserved only has pages
	 * that are usually filtered out while saving the vmcore.
	 */
	if (fdm->region_cnt > fdm->registered_regions) {
		pr_warn("Not all memory regions were saved!!!\n");
		pr_warn("  Unsaved memory regions:\n");
		i = fdm->registered_regions;
		while (i < fdm->region_cnt) {
			pr_warn("\t[%03d] base: 0x%llx, size: 0x%llx\n",
				i, fdm->rgn[i].src, fdm->rgn[i].size);
			i++;
		}

		pr_warn("If the unsaved regions only contain pages that are filtered out (eg. free/user pages), the vmcore should still be usable.\n");
		pr_warn("WARNING: If the unsaved regions contain kernel pages, the vmcore will be corrupted.\n");
	}

	fadump_conf->boot_mem_top = (fadump_conf->boot_memory_size + hole_size);
	fadump_conf->boot_mem_regs_cnt = fdm->region_cnt;
	opal_fadump_update_config(fadump_conf, fdm);
}