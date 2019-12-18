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
struct em_sti_priv {TYPE_1__* pdev; } ;
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_CLOCKEVENT ; 
 struct em_sti_priv* ced_to_em_sti (struct clock_event_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  em_sti_start (struct em_sti_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_sti_clock_event_set_oneshot(struct clock_event_device *ced)
{
	struct em_sti_priv *p = ced_to_em_sti(ced);

	dev_info(&p->pdev->dev, "used for oneshot clock events\n");
	em_sti_start(p, USER_CLOCKEVENT);
	return 0;
}