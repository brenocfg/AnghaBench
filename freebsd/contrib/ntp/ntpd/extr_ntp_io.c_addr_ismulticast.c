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
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 scalar_t__ IS_IPV6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_MCAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_boolean_t
addr_ismulticast(
	sockaddr_u *maddr
	)
{
	isc_boolean_t result;

#ifndef INCLUDE_IPV6_MULTICAST_SUPPORT
	/*
	 * If we don't have IPV6 support any IPV6 addr is not multicast
	 */
	if (IS_IPV6(maddr))
		result = ISC_FALSE;
	else
#endif
		result = IS_MCAST(maddr);

	if (!result)
		DPRINTF(4, ("address %s is not multicast\n",
			    stoa(maddr)));

	return result;
}