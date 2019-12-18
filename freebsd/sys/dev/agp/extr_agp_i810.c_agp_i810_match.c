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
struct agp_i810_match {int devid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIC_DISPLAY ; 
 scalar_t__ PCIS_DISPLAY_OTHER ; 
 scalar_t__ PCIS_DISPLAY_VGA ; 
 struct agp_i810_match const* agp_i810_matches ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct agp_i810_match*
agp_i810_match(device_t dev)
{
	int i, devid;

	if (pci_get_class(dev) != PCIC_DISPLAY
	    || (pci_get_subclass(dev) != PCIS_DISPLAY_VGA &&
	    pci_get_subclass(dev) != PCIS_DISPLAY_OTHER))
		return (NULL);

	devid = pci_get_devid(dev);
	for (i = 0; agp_i810_matches[i].devid != 0; i++) {
		if (agp_i810_matches[i].devid == devid)
			break;
	}
	if (agp_i810_matches[i].devid == 0)
		return (NULL);
	else
		return (&agp_i810_matches[i]);
}