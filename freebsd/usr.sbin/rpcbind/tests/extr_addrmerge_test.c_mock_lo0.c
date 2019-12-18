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

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  mock_ifaddr4 (char*,char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  mock_ifaddr6 (char*,char*,char*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mock_lo0(void)
{
	/* 
	 * This broadcast address looks wrong, but it's what getifaddrs(2)
	 * actually returns.  It's invalid because IFF_BROADCAST is not set
	 */
	mock_ifaddr4("lo0", "127.0.0.1", "255.0.0.0", "127.0.0.1",
	    IFF_LOOPBACK | IFF_UP | IFF_RUNNING | IFF_MULTICAST, false);
	mock_ifaddr6("lo0", "::1", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
	    "::1",
	    IFF_LOOPBACK | IFF_UP | IFF_RUNNING | IFF_MULTICAST, 0, false);
}