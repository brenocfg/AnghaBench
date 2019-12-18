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
struct sh_tmu_channel {TYPE_2__* tmu; int /*<<< orphan*/  enable_count; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __sh_tmu_enable (struct sh_tmu_channel*) ; 
 int /*<<< orphan*/  dev_pm_syscore_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh_tmu_enable(struct sh_tmu_channel *ch)
{
	if (ch->enable_count++ > 0)
		return 0;

	pm_runtime_get_sync(&ch->tmu->pdev->dev);
	dev_pm_syscore_device(&ch->tmu->pdev->dev, true);

	return __sh_tmu_enable(ch);
}