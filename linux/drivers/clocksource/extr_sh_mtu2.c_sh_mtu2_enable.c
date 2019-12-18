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
struct sh_mtu2_channel {TYPE_2__* mtu; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCR ; 
 unsigned long TCR_CCLR_TGRA ; 
 unsigned long TCR_TPSC_P64 ; 
 int /*<<< orphan*/  TGR ; 
 int /*<<< orphan*/  TIER ; 
 unsigned long TIER_TGIEA ; 
 unsigned long TIOC_IOCH (int /*<<< orphan*/ ) ; 
 unsigned long TIOC_IOCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIOR ; 
 int /*<<< orphan*/  TIOR_OC_0_CLEAR ; 
 int /*<<< orphan*/  TMDR ; 
 unsigned long TMDR_MD_NORMAL ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_syscore_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mtu2_start_stop_ch (struct sh_mtu2_channel*,int) ; 
 int /*<<< orphan*/  sh_mtu2_write (struct sh_mtu2_channel*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sh_mtu2_enable(struct sh_mtu2_channel *ch)
{
	unsigned long periodic;
	unsigned long rate;
	int ret;

	pm_runtime_get_sync(&ch->mtu->pdev->dev);
	dev_pm_syscore_device(&ch->mtu->pdev->dev, true);

	/* enable clock */
	ret = clk_enable(ch->mtu->clk);
	if (ret) {
		dev_err(&ch->mtu->pdev->dev, "ch%u: cannot enable clock\n",
			ch->index);
		return ret;
	}

	/* make sure channel is disabled */
	sh_mtu2_start_stop_ch(ch, 0);

	rate = clk_get_rate(ch->mtu->clk) / 64;
	periodic = (rate + HZ/2) / HZ;

	/*
	 * "Periodic Counter Operation"
	 * Clear on TGRA compare match, divide clock by 64.
	 */
	sh_mtu2_write(ch, TCR, TCR_CCLR_TGRA | TCR_TPSC_P64);
	sh_mtu2_write(ch, TIOR, TIOC_IOCH(TIOR_OC_0_CLEAR) |
		      TIOC_IOCL(TIOR_OC_0_CLEAR));
	sh_mtu2_write(ch, TGR, periodic);
	sh_mtu2_write(ch, TCNT, 0);
	sh_mtu2_write(ch, TMDR, TMDR_MD_NORMAL);
	sh_mtu2_write(ch, TIER, TIER_TGIEA);

	/* enable channel */
	sh_mtu2_start_stop_ch(ch, 1);

	return 0;
}