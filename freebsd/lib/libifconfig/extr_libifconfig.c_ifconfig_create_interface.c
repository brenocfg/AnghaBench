#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_5__ {int /*<<< orphan*/  errcode; void* errtype; } ;
struct TYPE_6__ {TYPE_1__ error; } ;
typedef  TYPE_2__ ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 void* OTHER ; 
 int /*<<< orphan*/  SIOCIFCREATE2 ; 
 scalar_t__ ifconfig_ioctlwrap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

int
ifconfig_create_interface(ifconfig_handle_t *h, const char *name, char **ifname)
{
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));

	(void)strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));

	/*
	 * TODO:
	 * Insert special snowflake handling here. See GitHub issue #12 for details.
	 * In the meantime, hard-nosupport interfaces that need special handling.
	 */
	if ((strncmp(name, "wlan",
	    strlen("wlan")) == 0) ||
	    (strncmp(name, "vlan",
	    strlen("vlan")) == 0) ||
	    (strncmp(name, "vxlan",
	    strlen("vxlan")) == 0)) {
		h->error.errtype = OTHER;
		h->error.errcode = ENOSYS;
		return (-1);
	}

	/* No special handling for this interface type. */
	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCIFCREATE2, &ifr) < 0) {
		return (-1);
	}

	*ifname = strdup(ifr.ifr_name);
	if (ifname == NULL) {
		h->error.errtype = OTHER;
		h->error.errcode = ENOMEM;
		return (-1);
	}

	return (0);
}