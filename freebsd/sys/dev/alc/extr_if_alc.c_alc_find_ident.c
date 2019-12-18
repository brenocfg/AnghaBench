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
typedef  scalar_t__ uint16_t ;
struct alc_ident {scalar_t__ vendorid; scalar_t__ deviceid; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct alc_ident* alc_ident_table ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct alc_ident *
alc_find_ident(device_t dev)
{
	struct alc_ident *ident;
	uint16_t vendor, devid;

	vendor = pci_get_vendor(dev);
	devid = pci_get_device(dev);
	for (ident = alc_ident_table; ident->name != NULL; ident++) {
		if (vendor == ident->vendorid && devid == ident->deviceid)
			return (ident);
	}

	return (NULL);
}