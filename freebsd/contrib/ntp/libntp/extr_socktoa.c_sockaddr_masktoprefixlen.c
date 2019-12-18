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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ isc_sockaddr_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_netaddr_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ isc_netaddr_masktoprefixlen (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

int
sockaddr_masktoprefixlen(
	const sockaddr_u *	psa
	)
{
	isc_netaddr_t	isc_na;
	isc_sockaddr_t	isc_sa;
	u_int		pfxlen;
	isc_result_t	result;
	int		rc;

	ZERO(isc_sa);
	memcpy(&isc_sa.type, psa,
	       min(sizeof(isc_sa.type), sizeof(*psa)));
	isc_netaddr_fromsockaddr(&isc_na, &isc_sa);
	result = isc_netaddr_masktoprefixlen(&isc_na, &pfxlen);
	rc = (ISC_R_SUCCESS == result)
		 ? (int)pfxlen
		 : -1;

	return rc;
}