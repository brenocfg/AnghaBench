#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct mpic_timer {void* dev; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 struct mpic_timer* get_timer (scalar_t__) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpic_free_timer (struct mpic_timer*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  timer_group_list ; 

struct mpic_timer *mpic_request_timer(irq_handler_t fn, void *dev,
				      time64_t time)
{
	struct mpic_timer *allocated_timer;
	int ret;

	if (list_empty(&timer_group_list))
		return NULL;

	if (time < 0)
		return NULL;

	allocated_timer = get_timer(time);
	if (!allocated_timer)
		return NULL;

	ret = request_irq(allocated_timer->irq, fn,
			IRQF_TRIGGER_LOW, "global-timer", dev);
	if (ret) {
		mpic_free_timer(allocated_timer);
		return NULL;
	}

	allocated_timer->dev = dev;

	return allocated_timer;
}