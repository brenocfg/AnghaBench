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
 int /*<<< orphan*/  SDHCI_LOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_UNLOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_init (struct sdhci_slot*) ; 

int
sdhci_generic_resume(struct sdhci_slot *slot)
{

	SDHCI_LOCK(slot);
	sdhci_init(slot);
	SDHCI_UNLOCK(slot);

	return (0);
}