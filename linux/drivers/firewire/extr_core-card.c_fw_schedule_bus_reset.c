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
struct fw_card {int br_short; int /*<<< orphan*/  br_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  fw_card_get (struct fw_card*) ; 
 int /*<<< orphan*/  fw_card_put (struct fw_card*) ; 
 int /*<<< orphan*/  fw_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fw_schedule_bus_reset(struct fw_card *card, bool delayed, bool short_reset)
{
	/* We don't try hard to sort out requests of long vs. short resets. */
	card->br_short = short_reset;

	/* Use an arbitrary short delay to combine multiple reset requests. */
	fw_card_get(card);
	if (!queue_delayed_work(fw_workqueue, &card->br_work,
				delayed ? DIV_ROUND_UP(HZ, 100) : 0))
		fw_card_put(card);
}