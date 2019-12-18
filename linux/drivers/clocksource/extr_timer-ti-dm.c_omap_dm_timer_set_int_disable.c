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
typedef  int u32 ;
struct TYPE_2__ {int tier; int twer; } ;
struct omap_dm_timer {int revision; TYPE_1__ context; int /*<<< orphan*/  irq_dis; int /*<<< orphan*/  irq_ena; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_TIMER_WAKEUP_EN_REG ; 
 int /*<<< orphan*/  omap_dm_timer_disable (struct omap_dm_timer*) ; 
 int /*<<< orphan*/  omap_dm_timer_enable (struct omap_dm_timer*) ; 
 int omap_dm_timer_read_reg (struct omap_dm_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dm_timer_write_reg (struct omap_dm_timer*,int /*<<< orphan*/ ,int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dm_timer_set_int_disable(struct omap_dm_timer *timer, u32 mask)
{
	u32 l = mask;

	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);

	if (timer->revision == 1)
		l = readl_relaxed(timer->irq_ena) & ~mask;

	writel_relaxed(l, timer->irq_dis);
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_WAKEUP_EN_REG) & ~mask;
	omap_dm_timer_write_reg(timer, OMAP_TIMER_WAKEUP_EN_REG, l);

	/* Save the context */
	timer->context.tier &= ~mask;
	timer->context.twer &= ~mask;
	omap_dm_timer_disable(timer);
	return 0;
}