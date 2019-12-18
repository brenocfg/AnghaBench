#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_tmu_channel {TYPE_1__* tmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TCR_TPSC_CLK4 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_start_stop_ch (struct sh_tmu_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sh_tmu_disable(struct sh_tmu_channel *ch)
{
	/* disable channel */
	sh_tmu_start_stop_ch(ch, 0);

	/* disable interrupts in TMU block */
	sh_tmu_write(ch, TCR, TCR_TPSC_CLK4);

	/* stop clock */
	clk_disable(ch->tmu->clk);
}