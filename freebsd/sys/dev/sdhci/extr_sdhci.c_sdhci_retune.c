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
struct sdhci_slot {int /*<<< orphan*/  retune_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_RETUNE_REQ_NEEDED ; 

__attribute__((used)) static void
sdhci_retune(void *arg)
{
	struct sdhci_slot *slot = arg;

	slot->retune_req |= SDHCI_RETUNE_REQ_NEEDED;
}