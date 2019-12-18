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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_finish_data (struct sdhci_slot*) ; 

__attribute__((used)) static void
bcm_sdhci_finish_transfer(device_t dev, struct sdhci_slot *slot)
{

	sdhci_finish_data(slot);
}