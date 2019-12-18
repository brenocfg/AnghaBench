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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct dc_type {scalar_t__ dc_devid; scalar_t__ dc_minrev; int /*<<< orphan*/ * dc_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dc_type* dc_devs ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct dc_type *
dc_devtype(device_t dev)
{
	const struct dc_type *t;
	uint32_t devid;
	uint8_t rev;

	t = dc_devs;
	devid = pci_get_devid(dev);
	rev = pci_get_revid(dev);

	while (t->dc_name != NULL) {
		if (devid == t->dc_devid && rev >= t->dc_minrev)
			return (t);
		t++;
	}

	return (NULL);
}