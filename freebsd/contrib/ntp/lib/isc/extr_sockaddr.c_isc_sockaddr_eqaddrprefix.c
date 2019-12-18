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
typedef  int /*<<< orphan*/  isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_netaddr_eqprefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

isc_boolean_t
isc_sockaddr_eqaddrprefix(const isc_sockaddr_t *a, const isc_sockaddr_t *b,
			  unsigned int prefixlen)
{
	isc_netaddr_t na, nb;
	isc_netaddr_fromsockaddr(&na, a);
	isc_netaddr_fromsockaddr(&nb, b);
	return (isc_netaddr_eqprefix(&na, &nb, prefixlen));
}