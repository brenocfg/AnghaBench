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
struct sh_tmu_channel {scalar_t__ enable_count; TYPE_2__* tmu; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __sh_tmu_disable (struct sh_tmu_channel*) ; 
 int /*<<< orphan*/  dev_pm_syscore_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_tmu_disable(struct sh_tmu_channel *ch)
{
	if (WARN_ON(ch->enable_count == 0))
		return;

	if (--ch->enable_count > 0)
		return;

	__sh_tmu_disable(ch);

	dev_pm_syscore_device(&ch->tmu->pdev->dev, false);
	pm_runtime_put(&ch->tmu->pdev->dev);
}