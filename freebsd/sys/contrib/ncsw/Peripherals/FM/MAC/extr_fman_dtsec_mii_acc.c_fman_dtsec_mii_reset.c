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
struct dtsec_mii_reg {int /*<<< orphan*/  miimcfg; } ;

/* Variables and functions */
 int MIIMCFG_RESET_MGMT ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_dtsec_mii_reset(struct dtsec_mii_reg *regs)
{
	/* Reset the management interface */
	iowrite32be(ioread32be(&regs->miimcfg) | MIIMCFG_RESET_MGMT,
			&regs->miimcfg);
	iowrite32be(ioread32be(&regs->miimcfg) & ~MIIMCFG_RESET_MGMT,
			&regs->miimcfg);
}