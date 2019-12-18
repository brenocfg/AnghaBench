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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct fman_kg_regs {int /*<<< orphan*/  fmkg_gcr; int /*<<< orphan*/  fmkg_gdv1r; int /*<<< orphan*/  fmkg_gdv0r; int /*<<< orphan*/  fmkg_fdor; int /*<<< orphan*/  fmkg_eeer; int /*<<< orphan*/  fmkg_eer; } ;

/* Variables and functions */
 int FMAN_MAX_NUM_OF_HW_PORTS ; 
 int FM_EX_KG_DOUBLE_ECC ; 
 int FM_EX_KG_KEYSIZE_OVERFLOW ; 
 int /*<<< orphan*/  clear_pe_all_cls_plan (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_pe_all_scheme (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_kg_init(struct fman_kg_regs *regs,
			uint32_t exceptions,
			uint32_t dflt_nia)
{
	uint32_t tmp;
	int i;

	iowrite32be(FM_EX_KG_DOUBLE_ECC | FM_EX_KG_KEYSIZE_OVERFLOW,
			&regs->fmkg_eer);

	tmp = 0;
	if (exceptions & FM_EX_KG_DOUBLE_ECC)
        	tmp |= FM_EX_KG_DOUBLE_ECC;

	if (exceptions & FM_EX_KG_KEYSIZE_OVERFLOW)
		tmp |= FM_EX_KG_KEYSIZE_OVERFLOW;

	iowrite32be(tmp, &regs->fmkg_eeer);
	iowrite32be(0, &regs->fmkg_fdor);
	iowrite32be(0, &regs->fmkg_gdv0r);
	iowrite32be(0, &regs->fmkg_gdv1r);
	iowrite32be(dflt_nia, &regs->fmkg_gcr);

	/* Clear binding between ports to schemes and classification plans
	 * so that all ports are not bound to any scheme/classification plan */
	for (i = 0; i < FMAN_MAX_NUM_OF_HW_PORTS; i++) {
		clear_pe_all_scheme(regs, (uint8_t)i);
		clear_pe_all_cls_plan(regs, (uint8_t)i);
	}
}