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
struct dtsec_regs {int /*<<< orphan*/  tctrl; int /*<<< orphan*/  rctrl; } ;

/* Variables and functions */
 int DTSEC_TCTRL_TTSE ; 
 int RCTRL_RTSE ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_dtsec_set_ts(struct dtsec_regs *regs, bool en)
{
	if (en) {
		iowrite32be(ioread32be(&regs->rctrl) | RCTRL_RTSE,
				&regs->rctrl);
		iowrite32be(ioread32be(&regs->tctrl) | DTSEC_TCTRL_TTSE,
				&regs->tctrl);
	} else {
		iowrite32be(ioread32be(&regs->rctrl) & ~RCTRL_RTSE,
				&regs->rctrl);
		iowrite32be(ioread32be(&regs->tctrl) & ~DTSEC_TCTRL_TTSE,
				&regs->tctrl);
	}
}