#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {char* name; int flags; } ;
typedef  TYPE_1__ pcap_if_t ;

/* Variables and functions */
 int PCAP_IF_CONNECTION_STATUS ; 
 int PCAP_IF_CONNECTION_STATUS_DISCONNECTED ; 
 int PCAP_IF_LOOPBACK ; 
 int PCAP_IF_RUNNING ; 
 int PCAP_IF_UP ; 
 int PCAP_IF_WIRELESS ; 
 int atoi (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static u_int
get_figure_of_merit(pcap_if_t *dev)
{
	const char *cp;
	u_int n;

	if (strcmp(dev->name, "any") == 0) {
		/*
		 * Give the "any" device an artificially high instance
		 * number, so it shows up after all other non-loopback
		 * interfaces.
		 */
		n = 0x1FFFFFFF;	/* 29 all-1 bits */
	} else {
		/*
		 * A number at the end of the device name string is
		 * assumed to be an instance number.  Add 1 to the
		 * instance number, and use 0 for "no instance
		 * number", so we don't put "no instance number"
		 * devices and "instance 0" devices together.
		 */
		cp = dev->name + strlen(dev->name) - 1;
		while (cp-1 >= dev->name && *(cp-1) >= '0' && *(cp-1) <= '9')
			cp--;
		if (*cp >= '0' && *cp <= '9')
			n = atoi(cp) + 1;
		else
			n = 0;
	}
	if (!(dev->flags & PCAP_IF_RUNNING))
		n |= 0x80000000;
	if (!(dev->flags & PCAP_IF_UP))
		n |= 0x40000000;

	/*
	 * Give non-wireless interfaces that aren't disconnected a better
	 * figure of merit than interfaces that are disconnected, as
	 * "disconnected" should indicate that the interface isn't
	 * plugged into a network and thus won't give you any traffic.
	 *
	 * For wireless interfaces, it means "associated with a network",
	 * which we presume not to necessarily prevent capture, as you
	 * might run the adapter in some flavor of monitor mode.
	 */
	if (!(dev->flags & PCAP_IF_WIRELESS) &&
	    (dev->flags & PCAP_IF_CONNECTION_STATUS) == PCAP_IF_CONNECTION_STATUS_DISCONNECTED)
		n |= 0x20000000;

	/*
	 * Sort loopback devices after non-loopback devices, *except* for
	 * disconnected devices.
	 */
	if (dev->flags & PCAP_IF_LOOPBACK)
		n |= 0x10000000;

	return (n);
}