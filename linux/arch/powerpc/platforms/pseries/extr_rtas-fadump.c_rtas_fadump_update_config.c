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
struct TYPE_2__ {int /*<<< orphan*/  destination_address; } ;
struct rtas_fadump_mem_struct {TYPE_1__ rmr_region; } ;
struct fw_dump {scalar_t__ boot_memory_size; scalar_t__ boot_mem_dest_addr; scalar_t__ fadumphdr_addr; } ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtas_fadump_update_config(struct fw_dump *fadump_conf,
				      const struct rtas_fadump_mem_struct *fdm)
{
	fadump_conf->boot_mem_dest_addr =
		be64_to_cpu(fdm->rmr_region.destination_address);

	fadump_conf->fadumphdr_addr = (fadump_conf->boot_mem_dest_addr +
				       fadump_conf->boot_memory_size);
}