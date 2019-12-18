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
 int EINVAL ; 
#define  PCI_FEATURE_AER 129 
#define  PCI_FEATURE_HP 128 

int
pcib_request_feature_allow(device_t pcib, device_t dev,
    enum pci_feature feature)
{
	/*
	 * No host firmware we have to negotiate with, so we allow
	 * every valid feature requested.
	 */
	switch (feature) {
	case PCI_FEATURE_AER:
	case PCI_FEATURE_HP:
		break;
	default:
		return (EINVAL);
	}

	return (0);
}