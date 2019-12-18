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
struct dtsec_regs {int /*<<< orphan*/  tmr_pemask; } ;

/* Variables and functions */
 int TMR_PEMASK_TSREEN ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_dtsec_disable_tmr_interrupt(struct dtsec_regs *regs)
{
	iowrite32be(ioread32be(&regs->tmr_pemask) & ~TMR_PEMASK_TSREEN,
			&regs->tmr_pemask);
}