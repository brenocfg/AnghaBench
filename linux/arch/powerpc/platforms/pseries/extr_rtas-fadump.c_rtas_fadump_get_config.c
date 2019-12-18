#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  destination_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  source_len; int /*<<< orphan*/  source_address; } ;
struct rtas_fadump_mem_struct {TYPE_1__ cpu_state_data; TYPE_2__ rmr_region; } ;
struct fw_dump {int boot_mem_regs_cnt; void* reserve_dump_area_start; void* boot_memory_size; void* boot_mem_top; void** boot_mem_sz; void** boot_mem_addr; } ;

/* Variables and functions */
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_fadump_update_config (struct fw_dump*,struct rtas_fadump_mem_struct const*) ; 

__attribute__((used)) static void rtas_fadump_get_config(struct fw_dump *fadump_conf,
				   const struct rtas_fadump_mem_struct *fdm)
{
	fadump_conf->boot_mem_addr[0] =
		be64_to_cpu(fdm->rmr_region.source_address);
	fadump_conf->boot_mem_sz[0] = be64_to_cpu(fdm->rmr_region.source_len);
	fadump_conf->boot_memory_size = fadump_conf->boot_mem_sz[0];

	fadump_conf->boot_mem_top = fadump_conf->boot_memory_size;
	fadump_conf->boot_mem_regs_cnt = 1;

	/*
	 * Start address of reserve dump area (permanent reservation) for
	 * re-registering FADump after dump capture.
	 */
	fadump_conf->reserve_dump_area_start =
		be64_to_cpu(fdm->cpu_state_data.destination_address);

	rtas_fadump_update_config(fadump_conf, fdm);
}