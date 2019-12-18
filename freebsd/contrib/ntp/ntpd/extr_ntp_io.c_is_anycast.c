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
 int /*<<< orphan*/  IN6_IFF_ANYCAST ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  check_flags6 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static isc_boolean_t
is_anycast(
	sockaddr_u *psau,
	const char *name
	)
{
#ifdef IN6_IFF_ANYCAST
	return check_flags6(psau, name, IN6_IFF_ANYCAST);
#else
	return ISC_FALSE;
#endif
}