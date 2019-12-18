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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_kg_regs {int /*<<< orphan*/ * fmkg_indirect; } ;
struct fman_kg_pe_regs {int /*<<< orphan*/  fmkg_pe_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_kg_write_sp(struct fman_kg_regs *regs, uint32_t sp, bool add)
{

	struct fman_kg_pe_regs *kgpe_regs;
	uint32_t tmp;

	kgpe_regs = (struct fman_kg_pe_regs *)&(regs->fmkg_indirect[0]);
	tmp = ioread32be(&kgpe_regs->fmkg_pe_sp);

	if (add)
		tmp |= sp;
	else /* clear */
		tmp &= ~sp;

	iowrite32be(tmp, &kgpe_regs->fmkg_pe_sp);

}