#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  un; int /*<<< orphan*/  in6; TYPE_1__ in; } ;
struct TYPE_8__ {int family; scalar_t__ zone; TYPE_2__ type; } ;
typedef  TYPE_3__ isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_netaddr_equal(const isc_netaddr_t *a, const isc_netaddr_t *b) {
	REQUIRE(a != NULL && b != NULL);

	if (a->family != b->family)
		return (ISC_FALSE);

	if (a->zone != b->zone)
		return (ISC_FALSE);

	switch (a->family) {
	case AF_INET:
		if (a->type.in.s_addr != b->type.in.s_addr)
			return (ISC_FALSE);
		break;
	case AF_INET6:
		if (memcmp(&a->type.in6, &b->type.in6,
			   sizeof(a->type.in6)) != 0 ||
		    a->zone != b->zone)
			return (ISC_FALSE);
		break;
#ifdef ISC_PLATFORM_HAVESYSUNH
	case AF_UNIX:
		if (strcmp(a->type.un, b->type.un) != 0)
			return (ISC_FALSE);
		break;
#endif
	default:
		return (ISC_FALSE);
	}
	return (ISC_TRUE);
}