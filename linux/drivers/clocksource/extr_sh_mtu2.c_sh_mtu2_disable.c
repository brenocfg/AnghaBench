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
struct sh_mtu2_channel {TYPE_2__* mtu; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_syscore_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mtu2_start_stop_ch (struct sh_mtu2_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mtu2_disable(struct sh_mtu2_channel *ch)
{
	/* disable channel */
	sh_mtu2_start_stop_ch(ch, 0);

	/* stop clock */
	clk_disable(ch->mtu->clk);

	dev_pm_syscore_device(&ch->mtu->pdev->dev, false);
	pm_runtime_put(&ch->mtu->pdev->dev);
}