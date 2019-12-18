#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct arizona_extcon_info {TYPE_2__ micd_detect_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  detecting; TYPE_2__ micd_timeout_work; struct arizona* arizona; } ;
struct TYPE_4__ {int micd_detect_debounce; } ;
struct arizona {TYPE_1__ pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  arizona_micd_detect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static irqreturn_t arizona_micdet(int irq, void *data)
{
	struct arizona_extcon_info *info = data;
	struct arizona *arizona = info->arizona;
	int debounce = arizona->pdata.micd_detect_debounce;

	cancel_delayed_work_sync(&info->micd_detect_work);
	cancel_delayed_work_sync(&info->micd_timeout_work);

	mutex_lock(&info->lock);
	if (!info->detecting)
		debounce = 0;
	mutex_unlock(&info->lock);

	if (debounce)
		queue_delayed_work(system_power_efficient_wq,
				   &info->micd_detect_work,
				   msecs_to_jiffies(debounce));
	else
		arizona_micd_detect(&info->micd_detect_work.work);

	return IRQ_HANDLED;
}