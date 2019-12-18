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
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int sc_probe_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scprobe(device_t dev)
{

	/* No pnp support */
	if (isa_get_vendorid(dev))
		return (ENXIO);

	device_set_desc(dev, "System console");
	return (sc_probe_unit(device_get_unit(dev), device_get_flags(dev)));
}