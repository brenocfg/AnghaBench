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
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int /*<<< orphan*/  mock_ifaddr4 (char*,char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  mock_ifaddr6 (char*,char*,char*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mock_igb2(void)
{
	mock_ifaddr4("igb2", "192.0.2.130", "255.255.255.128", "192.0.2.255",
	    IFF_UP | IFF_BROADCAST | IFF_RUNNING | IFF_SIMPLEX | IFF_MULTICAST,
	    false);
	mock_ifaddr6("igb2", "2001:db8:1::2", "ffff:ffff:ffff:ffff::",
	    "2001:db8:1:0:ffff:ffff:ffff:ffff",
	    IFF_UP | IFF_BROADCAST | IFF_RUNNING | IFF_SIMPLEX | IFF_MULTICAST,
	    0, false);
}