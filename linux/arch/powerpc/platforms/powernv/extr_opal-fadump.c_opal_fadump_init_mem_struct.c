#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct fw_dump {int boot_mem_regs_cnt; scalar_t__ boot_memory_size; scalar_t__* boot_mem_sz; int /*<<< orphan*/ * boot_mem_addr; int /*<<< orphan*/  kernel_metadata; scalar_t__ reserve_dump_area_start; } ;
struct TYPE_7__ {TYPE_1__* rgn; scalar_t__ fadumphdr_addr; int /*<<< orphan*/  region_cnt; } ;
struct TYPE_6__ {scalar_t__ dest; scalar_t__ size; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 TYPE_2__* __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_fadump_init_metadata (TYPE_2__*) ; 
 int /*<<< orphan*/  opal_fadump_update_config (struct fw_dump*,TYPE_2__*) ; 
 TYPE_2__* opal_fdm ; 

__attribute__((used)) static u64 opal_fadump_init_mem_struct(struct fw_dump *fadump_conf)
{
	u64 addr = fadump_conf->reserve_dump_area_start;
	int i;

	opal_fdm = __va(fadump_conf->kernel_metadata);
	opal_fadump_init_metadata(opal_fdm);

	/* Boot memory regions */
	for (i = 0; i < fadump_conf->boot_mem_regs_cnt; i++) {
		opal_fdm->rgn[i].src	= fadump_conf->boot_mem_addr[i];
		opal_fdm->rgn[i].dest	= addr;
		opal_fdm->rgn[i].size	= fadump_conf->boot_mem_sz[i];

		opal_fdm->region_cnt++;
		addr += fadump_conf->boot_mem_sz[i];
	}

	/*
	 * Kernel metadata is passed to f/w and retrieved in capture kerenl.
	 * So, use it to save fadump header address instead of calculating it.
	 */
	opal_fdm->fadumphdr_addr = (opal_fdm->rgn[0].dest +
				    fadump_conf->boot_memory_size);

	opal_fadump_update_config(fadump_conf, opal_fdm);

	return addr;
}