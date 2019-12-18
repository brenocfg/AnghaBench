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
 int BUS_PROBE_GENERIC ; 
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int TYPE_NONE ; 
 int /*<<< orphan*/ * desc_strings ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nxprtc_get_chiptype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nxprtc_probe(device_t dev)
{
	int chiptype, rv;

#ifdef FDT
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);
	rv = BUS_PROBE_GENERIC;
#else
	rv = BUS_PROBE_NOWILDCARD;
#endif
	if ((chiptype = nxprtc_get_chiptype(dev)) == TYPE_NONE)
		return (ENXIO);

	device_set_desc(dev, desc_strings[chiptype]);
	return (rv);
}