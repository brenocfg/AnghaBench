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
struct fman_prs_regs {int /*<<< orphan*/  fmpr_rpimac; } ;

/* Variables and functions */
 int FM_PCD_PRS_RPIMAC_EN ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

int fman_prs_is_enabled(struct fman_prs_regs *regs)
{
	return ioread32be(&regs->fmpr_rpimac) & FM_PCD_PRS_RPIMAC_EN;
}