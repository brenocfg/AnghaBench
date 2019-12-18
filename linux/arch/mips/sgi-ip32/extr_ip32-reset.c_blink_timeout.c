#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {unsigned long misc; } ;
struct TYPE_5__ {TYPE_1__ ctrl; } ;
struct TYPE_6__ {TYPE_2__ perif; } ;

/* Variables and functions */
 unsigned long MACEISA_LED_RED ; 
 int /*<<< orphan*/  blink_timer ; 
 scalar_t__ blink_timer_timeout ; 
 scalar_t__ jiffies ; 
 TYPE_3__* mace ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void blink_timeout(struct timer_list *unused)
{
	unsigned long led = mace->perif.ctrl.misc ^ MACEISA_LED_RED;
	mace->perif.ctrl.misc = led;
	mod_timer(&blink_timer, jiffies + blink_timer_timeout);
}