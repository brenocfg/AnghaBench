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
typedef  scalar_t__ u_int16_t ;
struct aac_ident {scalar_t__ vendor; scalar_t__ device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct aac_ident* aacraid_family_identifiers ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct aac_ident *
aac_find_ident(device_t dev)
{
	struct aac_ident *m;
	u_int16_t vendid, devid;

	vendid = pci_get_vendor(dev);
	devid = pci_get_device(dev);

	for (m = aacraid_family_identifiers; m->vendor != 0; m++) {
		if ((m->vendor == vendid) && (m->device == devid))
			return (m);
	}

	return (NULL);
}