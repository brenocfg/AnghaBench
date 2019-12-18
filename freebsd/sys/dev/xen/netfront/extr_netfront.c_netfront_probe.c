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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xen_disable_pv_nics ; 
 scalar_t__ xen_hvm_domain () ; 
 int /*<<< orphan*/  xenbus_get_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netfront_probe(device_t dev)
{

	if (xen_hvm_domain() && xen_disable_pv_nics != 0)
		return (ENXIO);

	if (!strcmp(xenbus_get_type(dev), "vif")) {
		device_set_desc(dev, "Virtual Network Interface");
		return (0);
	}

	return (ENXIO);
}