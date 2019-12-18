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
struct sdhci_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_card_task (struct sdhci_slot*,int /*<<< orphan*/ ) ; 

void
sdhci_start_slot(struct sdhci_slot *slot)
{

	sdhci_card_task(slot, 0);
}