#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32 ;
struct TYPE_6__ {int sa_family; } ;
struct TYPE_7__ {TYPE_1__ sa; } ;
typedef  TYPE_2__ sockaddr_u ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ IN6_IFF_DEPARTED ; 
 scalar_t__ IN6_IFF_DETACHED ; 
 scalar_t__ IN6_IFF_TENTATIVE ; 
 scalar_t__ IN_IFF_DETACHED ; 
 scalar_t__ IN_IFF_TENTATIVE ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  check_flags (TYPE_2__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  check_flags6 (TYPE_2__*,char const*,scalar_t__) ; 

__attribute__((used)) static isc_boolean_t
is_valid(
	sockaddr_u *psau,
	const char *name
	)
{
	u_int32 flags;

	flags = 0;
	switch (psau->sa.sa_family) {
	case AF_INET:
#ifdef IN_IFF_DETACHED
		flags |= IN_IFF_DETACHED;
#endif
#ifdef IN_IFF_TENTATIVE
		flags |= IN_IFF_TENTATIVE;
#endif
		return check_flags(psau, name, flags) ? ISC_FALSE : ISC_TRUE;
	case AF_INET6:
#ifdef IN6_IFF_DEPARTED
		flags |= IN6_IFF_DEPARTED;
#endif
#ifdef IN6_IFF_DETACHED
		flags |= IN6_IFF_DETACHED;
#endif
#ifdef IN6_IFF_TENTATIVE
		flags |= IN6_IFF_TENTATIVE;
#endif
		return check_flags6(psau, name, flags) ? ISC_FALSE : ISC_TRUE;
	default:
		return ISC_FALSE;
	}
}