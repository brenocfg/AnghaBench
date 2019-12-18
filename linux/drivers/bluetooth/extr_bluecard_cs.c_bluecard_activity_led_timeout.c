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
struct timer_list {int dummy; } ;
struct bluecard_info {int /*<<< orphan*/  timer; int /*<<< orphan*/  hw_state; TYPE_2__* p_dev; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ACTIVITY ; 
 int HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bluecard_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct bluecard_info* info ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void bluecard_activity_led_timeout(struct timer_list *t)
{
	struct bluecard_info *info = from_timer(info, t, timer);
	unsigned int iobase = info->p_dev->resource[0]->start;

	if (test_bit(CARD_ACTIVITY, &(info->hw_state))) {
		/* leave LED in inactive state for HZ/10 for blink effect */
		clear_bit(CARD_ACTIVITY, &(info->hw_state));
		mod_timer(&(info->timer), jiffies + HZ / 10);
	}

	/* Disable activity LED, enable power LED */
	outb(0x08 | 0x20, iobase + 0x30);
}