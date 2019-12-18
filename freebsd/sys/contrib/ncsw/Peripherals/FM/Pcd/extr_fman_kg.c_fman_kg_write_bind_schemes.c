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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_kg_regs {int /*<<< orphan*/ * fmkg_indirect; } ;
struct fman_kg_pe_regs {int /*<<< orphan*/  fmkg_pe_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  build_ar_bind_scheme (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fman_kg_write_ar_wait (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_kg_write_bind_schemes(struct fman_kg_regs *regs,
				uint8_t hwport_id,
				uint32_t schemes)
{
	struct fman_kg_pe_regs *kg_pe_regs;
	uint32_t tmp_reg;
	int err;

	kg_pe_regs = (struct fman_kg_pe_regs *)&(regs->fmkg_indirect[0]);

	iowrite32be(schemes, &kg_pe_regs->fmkg_pe_sp);

	tmp_reg = build_ar_bind_scheme(hwport_id, TRUE);
	err = fman_kg_write_ar_wait(regs, tmp_reg);
	return err;
}