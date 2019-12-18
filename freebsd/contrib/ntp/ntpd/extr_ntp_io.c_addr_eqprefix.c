#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_netaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 scalar_t__ isc_netaddr_eqprefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static int
addr_eqprefix(
	const sockaddr_u *	a,
	const sockaddr_u *	b,
	int			prefixlen
	)
{
	isc_netaddr_t		isc_a;
	isc_netaddr_t		isc_b;
	isc_sockaddr_t		isc_sa;

	ZERO(isc_sa);
	memcpy(&isc_sa.type, a, min(sizeof(isc_sa.type), sizeof(*a)));
	isc_netaddr_fromsockaddr(&isc_a, &isc_sa);

	ZERO(isc_sa);
	memcpy(&isc_sa.type, b, min(sizeof(isc_sa.type), sizeof(*b)));
	isc_netaddr_fromsockaddr(&isc_b, &isc_sa);

	return (int)isc_netaddr_eqprefix(&isc_a, &isc_b,
					 (u_int)prefixlen);
}