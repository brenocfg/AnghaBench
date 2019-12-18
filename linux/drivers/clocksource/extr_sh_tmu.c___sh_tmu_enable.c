#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_tmu_channel {int /*<<< orphan*/  index; TYPE_2__* tmu; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCOR ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_TPSC_CLK4 ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_start_stop_ch (struct sh_tmu_channel*,int) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __sh_tmu_enable(struct sh_tmu_channel *ch)
{
	int ret;

	/* enable clock */
	ret = clk_enable(ch->tmu->clk);
	if (ret) {
		dev_err(&ch->tmu->pdev->dev, "ch%u: cannot enable clock\n",
			ch->index);
		return ret;
	}

	/* make sure channel is disabled */
	sh_tmu_start_stop_ch(ch, 0);

	/* maximum timeout */
	sh_tmu_write(ch, TCOR, 0xffffffff);
	sh_tmu_write(ch, TCNT, 0xffffffff);

	/* configure channel to parent clock / 4, irq off */
	sh_tmu_write(ch, TCR, TCR_TPSC_CLK4);

	/* enable channel */
	sh_tmu_start_stop_ch(ch, 1);

	return 0;
}