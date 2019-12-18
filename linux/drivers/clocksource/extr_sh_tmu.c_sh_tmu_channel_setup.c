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
struct sh_tmu_device {scalar_t__ model; TYPE_1__* pdev; scalar_t__ mapbase; } ;
struct sh_tmu_channel {unsigned int index; scalar_t__ irq; int cs_enabled; scalar_t__ enable_count; scalar_t__ base; struct sh_tmu_device* tmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SH_TMU_SH3 ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (TYPE_1__*,unsigned int) ; 
 int sh_tmu_register (struct sh_tmu_channel*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sh_tmu_channel_setup(struct sh_tmu_channel *ch, unsigned int index,
				bool clockevent, bool clocksource,
				struct sh_tmu_device *tmu)
{
	/* Skip unused channels. */
	if (!clockevent && !clocksource)
		return 0;

	ch->tmu = tmu;
	ch->index = index;

	if (tmu->model == SH_TMU_SH3)
		ch->base = tmu->mapbase + 4 + ch->index * 12;
	else
		ch->base = tmu->mapbase + 8 + ch->index * 12;

	ch->irq = platform_get_irq(tmu->pdev, index);
	if (ch->irq < 0)
		return ch->irq;

	ch->cs_enabled = false;
	ch->enable_count = 0;

	return sh_tmu_register(ch, dev_name(&tmu->pdev->dev),
			       clockevent, clocksource);
}