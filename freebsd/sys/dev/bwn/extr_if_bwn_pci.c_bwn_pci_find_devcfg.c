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
struct bwn_pci_device {scalar_t__ device; scalar_t__ vendor; } ;
struct bwn_pci_devcfg {struct bwn_pci_device* devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 struct bwn_pci_devcfg* bwn_pci_devcfgs ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_pci_find_devcfg(device_t dev, const struct bwn_pci_devcfg **cfg,
    const struct bwn_pci_device **device)
{
	const struct bwn_pci_devcfg	*dvc;
	const struct bwn_pci_device	*dv;

	for (dvc = bwn_pci_devcfgs; dvc->devices != NULL; dvc++) {
		for (dv = dvc->devices; dv->device != 0; dv++) {
			if (pci_get_vendor(dev) == dv->vendor &&
			    pci_get_device(dev) == dv->device)
			{
				if (cfg != NULL)
					*cfg = dvc;
				
				if (device != NULL)
					*device = dv;
				
				return (0);
			}
		}
	}

	return (ENOENT);
}