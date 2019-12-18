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

/* Variables and functions */
 int BUS_CHILD_PNPINFO_STR (scalar_t__,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  bhnd_get_device (scalar_t__) ; 
 int /*<<< orphan*/  bhnd_get_hwrev (scalar_t__) ; 
 int /*<<< orphan*/  bhnd_get_vendor (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_child_pnpinfo_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	if (device_get_parent(child) != dev) {
		return (BUS_CHILD_PNPINFO_STR(device_get_parent(dev), child,
		    buf, buflen));
	}

	snprintf(buf, buflen, "vendor=0x%hx device=0x%hx rev=0x%hhx",
	    bhnd_get_vendor(child), bhnd_get_device(child),
	    bhnd_get_hwrev(child));

	return (0);
}