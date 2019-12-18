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
typedef  int /*<<< orphan*/  u8 ;
struct mbus_dram_window {int base; int size; int /*<<< orphan*/  mbus_attr; } ;
struct mbus_dram_target_info {int num_cs; int /*<<< orphan*/  mbus_dram_target_id; struct mbus_dram_window* cs; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct mbus_dram_target_info* mv_mbus_dram_info () ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int mvebu_mbus_get_dram_win_info(phys_addr_t phyaddr, u8 *target, u8 *attr)
{
	const struct mbus_dram_target_info *dram;
	int i;

	/* Get dram info */
	dram = mv_mbus_dram_info();
	if (!dram) {
		pr_err("missing DRAM information\n");
		return -ENODEV;
	}

	/* Try to find matching DRAM window for phyaddr */
	for (i = 0; i < dram->num_cs; i++) {
		const struct mbus_dram_window *cs = dram->cs + i;

		if (cs->base <= phyaddr &&
			phyaddr <= (cs->base + cs->size - 1)) {
			*target = dram->mbus_dram_target_id;
			*attr = cs->mbus_attr;
			return 0;
		}
	}

	pr_err("invalid dram address %pa\n", &phyaddr);
	return -EINVAL;
}