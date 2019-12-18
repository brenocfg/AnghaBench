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
struct opal_fadump_mem_struct {int /*<<< orphan*/  fadumphdr_addr; TYPE_1__* rgn; int /*<<< orphan*/  region_cnt; } ;
struct fw_dump {int /*<<< orphan*/  fadumphdr_addr; int /*<<< orphan*/  boot_mem_dest_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opal_fadump_update_config(struct fw_dump *fadump_conf,
				      const struct opal_fadump_mem_struct *fdm)
{
	pr_debug("Boot memory regions count: %d\n", fdm->region_cnt);

	/*
	 * The destination address of the first boot memory region is the
	 * destination address of boot memory regions.
	 */
	fadump_conf->boot_mem_dest_addr = fdm->rgn[0].dest;
	pr_debug("Destination address of boot memory regions: %#016llx\n",
		 fadump_conf->boot_mem_dest_addr);

	fadump_conf->fadumphdr_addr = fdm->fadumphdr_addr;
}