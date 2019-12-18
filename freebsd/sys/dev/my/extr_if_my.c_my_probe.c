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
struct my_type {scalar_t__ my_vid; scalar_t__ my_did; int /*<<< orphan*/ * my_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct my_type* my_devs ; 
 struct my_type* my_info_tmp ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
my_probe(device_t dev)
{
	struct my_type *t;

	t = my_devs;
	while (t->my_name != NULL) {
		if ((pci_get_vendor(dev) == t->my_vid) &&
		    (pci_get_device(dev) == t->my_did)) {
			device_set_desc(dev, t->my_name);
			my_info_tmp = t;
			return (BUS_PROBE_DEFAULT);
		}
		t++;
	}
	return (ENXIO);
}