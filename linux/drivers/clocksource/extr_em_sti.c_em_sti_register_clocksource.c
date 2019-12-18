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
struct clocksource {int rating; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  resume; void* suspend; void* disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct em_sti_priv {int /*<<< orphan*/  rate; TYPE_1__* pdev; struct clocksource cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 int /*<<< orphan*/  CLOCK_SOURCE_IS_CONTINUOUS ; 
 int /*<<< orphan*/  clocksource_register_hz (struct clocksource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 void* em_sti_clocksource_disable ; 
 int /*<<< orphan*/  em_sti_clocksource_enable ; 
 int /*<<< orphan*/  em_sti_clocksource_read ; 
 int /*<<< orphan*/  em_sti_clocksource_resume ; 

__attribute__((used)) static int em_sti_register_clocksource(struct em_sti_priv *p)
{
	struct clocksource *cs = &p->cs;

	cs->name = dev_name(&p->pdev->dev);
	cs->rating = 200;
	cs->read = em_sti_clocksource_read;
	cs->enable = em_sti_clocksource_enable;
	cs->disable = em_sti_clocksource_disable;
	cs->suspend = em_sti_clocksource_disable;
	cs->resume = em_sti_clocksource_resume;
	cs->mask = CLOCKSOURCE_MASK(48);
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;

	dev_info(&p->pdev->dev, "used as clock source\n");

	clocksource_register_hz(cs, p->rate);
	return 0;
}