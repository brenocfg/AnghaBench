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
struct bluecard_info {int /*<<< orphan*/  timer; int /*<<< orphan*/  hw_state; TYPE_2__* p_dev; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ACTIVITY ; 
 int /*<<< orphan*/  CARD_HAS_ACTIVITY_LED ; 
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bluecard_enable_activity_led(struct bluecard_info *info)
{
	unsigned int iobase = info->p_dev->resource[0]->start;

	/* don't disturb running blink timer */
	if (timer_pending(&(info->timer)))
		return;

	set_bit(CARD_ACTIVITY, &(info->hw_state));

	if (test_bit(CARD_HAS_ACTIVITY_LED, &(info->hw_state))) {
		/* Enable activity LED, keep power LED enabled */
		outb(0x18 | 0x60, iobase + 0x30);
	} else {
		/* Disable power LED */
		outb(0x00, iobase + 0x30);
	}

	/* Stop the LED after HZ/10 */
	mod_timer(&(info->timer), jiffies + HZ / 10);
}