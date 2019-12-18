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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_kg_regs {int /*<<< orphan*/ * fmkg_indirect; } ;
struct fman_kg_cp_regs {int /*<<< orphan*/ * kgcpe; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FM_KG_CLS_PLAN_GRPS_NUM ; 
 int FM_KG_NUM_CLS_PLAN_ENTR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  build_ar_cls_plan (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int fman_kg_write_ar_wait (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_kg_write_cls_plan(struct fman_kg_regs *regs,
				uint8_t grp_id,
				uint8_t entries_mask,
				uint8_t hwport_id,
				struct fman_kg_cp_regs *cls_plan_regs)
{
	struct fman_kg_cp_regs *kgcpe_regs;
	uint32_t tmp_reg;
	int i, err;

	/* Check group index is valid and the group isn't empty */
	if (grp_id >= FM_KG_CLS_PLAN_GRPS_NUM)
		return -EINVAL;

	/* Write indirect classification plan registers */
	kgcpe_regs = (struct fman_kg_cp_regs *)&(regs->fmkg_indirect[0]);

	for (i = 0; i < FM_KG_NUM_CLS_PLAN_ENTR; i++) {
		iowrite32be(cls_plan_regs->kgcpe[i], &kgcpe_regs->kgcpe[i]);
	}

	tmp_reg = build_ar_cls_plan(grp_id, entries_mask, hwport_id, TRUE);
	err = fman_kg_write_ar_wait(regs, tmp_reg);
	return err;
}