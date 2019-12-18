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
typedef  int /*<<< orphan*/  u_short ;
struct libalias {int dummy; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,struct in_addr*,struct in_addr*,int) ; 
 struct in_addr FindAliasAddress (struct libalias*,struct in_addr) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int PKT_ALIAS_OK ; 

__attribute__((used)) static int
FragmentOut(struct libalias *la, struct in_addr *ip_src, u_short *ip_sum)
{
	struct in_addr alias_address;

	LIBALIAS_LOCK_ASSERT(la);
	alias_address = FindAliasAddress(la, *ip_src);
	DifferentialChecksum(ip_sum,
	    &alias_address, ip_src, 2);
	*ip_src = alias_address;

	return (PKT_ALIAS_OK);
}