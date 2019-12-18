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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mid_pwr {scalar_t__ available; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int) ; 
 int mid_pwr_set_power_state (struct mid_pwr*,struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct mid_pwr* midpwr ; 
 int /*<<< orphan*/  might_sleep () ; 

int intel_mid_pci_set_power_state(struct pci_dev *pdev, pci_power_t state)
{
	struct mid_pwr *pwr = midpwr;
	int ret = 0;

	might_sleep();

	if (pwr && pwr->available)
		ret = mid_pwr_set_power_state(pwr, pdev, state);
	dev_vdbg(&pdev->dev, "set_power_state() returns %d\n", ret);

	return 0;
}