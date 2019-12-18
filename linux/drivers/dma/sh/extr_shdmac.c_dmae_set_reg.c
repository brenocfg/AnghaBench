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
struct sh_dmae_regs {int sar; int dar; int tcr; } ;
struct sh_dmae_chan {int xmit_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAR ; 
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  sh_dmae_writel (struct sh_dmae_chan*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmae_set_reg(struct sh_dmae_chan *sh_chan, struct sh_dmae_regs *hw)
{
	sh_dmae_writel(sh_chan, hw->sar, SAR);
	sh_dmae_writel(sh_chan, hw->dar, DAR);
	sh_dmae_writel(sh_chan, hw->tcr >> sh_chan->xmit_shift, TCR);
}