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
typedef  int uint8_t ;
struct fman_kg_cp_regs {int /*<<< orphan*/ * kgcpe; } ;
struct fman_kg_cls_plan_params {int entries_mask; int /*<<< orphan*/ * mask_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fman_kg_cp_regs*,int /*<<< orphan*/ ,int) ; 

int fman_kg_build_cls_plan(struct fman_kg_cls_plan_params *params,
				struct fman_kg_cp_regs *cls_plan_regs)
{
	uint8_t entries_set, entry_bit;
	int i;

	/* Zero out all group's register */
	memset(cls_plan_regs, 0, sizeof(struct fman_kg_cp_regs));

	/* Go over all classification entries in params->entries_mask and
	 * configure the corresponding cpe register */
	entries_set = params->entries_mask;
	for (i = 0; entries_set; i++) {
		entry_bit = (uint8_t)(0x80 >> i);
		if ((entry_bit & entries_set) == 0)
			continue;
		entries_set ^= entry_bit;
		cls_plan_regs->kgcpe[i] = params->mask_vector[i];
	}

	return 0;
}