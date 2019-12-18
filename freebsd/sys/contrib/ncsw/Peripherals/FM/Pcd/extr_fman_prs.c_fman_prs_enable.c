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
typedef  int uint32_t ;
struct fman_prs_regs {int /*<<< orphan*/  fmpr_rpimac; } ;

/* Variables and functions */
 int FM_PCD_PRS_RPIMAC_EN ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_prs_enable(struct fman_prs_regs *regs)
{
	uint32_t tmp;

	tmp = ioread32be(&regs->fmpr_rpimac) | FM_PCD_PRS_RPIMAC_EN;
	iowrite32be(tmp, &regs->fmpr_rpimac);
}