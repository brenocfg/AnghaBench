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
typedef  enum pci_feature { ____Placeholder_pci_feature } pci_feature ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_REQUEST_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
pcib_request_feature(device_t dev, enum pci_feature feature)
{

	/*
	 * Invoke PCIB_REQUEST_FEATURE of this bridge first in case
	 * the firmware overrides the method of PCI-PCI bridges.
	 */
	return (PCIB_REQUEST_FEATURE(dev, dev, feature));
}