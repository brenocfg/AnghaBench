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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdhci_slot {int opt; scalar_t__ retune_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_INT_RETUNE ; 
 int /*<<< orphan*/  SDHCI_INT_TUNEERR ; 
 scalar_t__ SDHCI_RETUNE_MODE_2 ; 
 scalar_t__ SDHCI_RETUNE_MODE_3 ; 
 int SDHCI_TUNING_ENABLED ; 

__attribute__((used)) static uint32_t
sdhci_tuning_intmask(const struct sdhci_slot *slot)
{
	uint32_t intmask;

	intmask = 0;
	if (slot->opt & SDHCI_TUNING_ENABLED) {
		intmask |= SDHCI_INT_TUNEERR;
		if (slot->retune_mode == SDHCI_RETUNE_MODE_2 ||
		    slot->retune_mode == SDHCI_RETUNE_MODE_3)
			intmask |= SDHCI_INT_RETUNE;
	}
	return (intmask);
}