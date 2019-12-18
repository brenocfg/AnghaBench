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
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int BUS_CHILD_LOCATION_STR (scalar_t__,scalar_t__,char*,size_t) ; 
 scalar_t__ bhnd_get_region_addr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned long long) ; 

__attribute__((used)) static int
bhnd_child_location_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	bhnd_addr_t	addr;
	bhnd_size_t	size;
	
	if (device_get_parent(child) != dev) {
		return (BUS_CHILD_LOCATION_STR(device_get_parent(dev), child,
		    buf, buflen));
	}


	if (bhnd_get_region_addr(child, BHND_PORT_DEVICE, 0, 0, &addr, &size)) {
		/* No device default port/region */
		if (buflen > 0)
			*buf = '\0';
		return (0);
	}

	snprintf(buf, buflen, "port0.0=0x%llx", (unsigned long long) addr);
	return (0);
}