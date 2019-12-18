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
struct sdhci_slot {int card_present; int /*<<< orphan*/  card_task; int /*<<< orphan*/  card_delayed_task; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_INSERT_DELAY_TICKS ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_swi_giant ; 

__attribute__((used)) static void
sdhci_handle_card_present_locked(struct sdhci_slot *slot, bool is_present)
{
	bool was_present;

	/*
	 * If there was no card and now there is one, schedule the task to
	 * create the child device after a short delay.  The delay is to
	 * debounce the card insert (sometimes the card detect pin stabilizes
	 * before the other pins have made good contact).
	 *
	 * If there was a card present and now it's gone, immediately schedule
	 * the task to delete the child device.  No debouncing -- gone is gone,
	 * because once power is removed, a full card re-init is needed, and
	 * that happens by deleting and recreating the child device.
	 */
#ifdef MMCCAM
	was_present = slot->card_present;
#else
	was_present = slot->dev != NULL;
#endif
	if (!was_present && is_present) {
		taskqueue_enqueue_timeout(taskqueue_swi_giant,
		    &slot->card_delayed_task, -SDHCI_INSERT_DELAY_TICKS);
	} else if (was_present && !is_present) {
		taskqueue_enqueue(taskqueue_swi_giant, &slot->card_task);
	}
}