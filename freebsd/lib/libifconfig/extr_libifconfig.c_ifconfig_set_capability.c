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
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_name; } ;
struct ifconfig_capabilities {int curcap; int reqcap; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  SIOCSIFCAP ; 
 scalar_t__ ifconfig_get_capability (int /*<<< orphan*/ *,char const*,struct ifconfig_capabilities*) ; 
 scalar_t__ ifconfig_ioctlwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_set_capability(ifconfig_handle_t *h, const char *name,
    const int capability)
{
	struct ifreq ifr;
	struct ifconfig_capabilities ifcap;
	int flags, value;

	memset(&ifr, 0, sizeof(ifr));

	if (ifconfig_get_capability(h, name, &ifcap) != 0) {
		return (-1);
	}

	value = capability;
	flags = ifcap.curcap;
	if (value < 0) {
		value = -value;
		flags &= ~value;
	} else {
		flags |= value;
	}
	flags &= ifcap.reqcap;

	(void)strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));

	/*
	 * TODO: Verify that it's safe to not have ifr.ifr_curcap
	 * set for this request.
	 */
	ifr.ifr_reqcap = flags;
	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCSIFCAP, &ifr) < 0) {
		return (-1);
	}
	return (0);
}