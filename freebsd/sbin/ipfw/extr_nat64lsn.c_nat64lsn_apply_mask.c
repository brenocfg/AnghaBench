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
typedef  int /*<<< orphan*/  uint16_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  APPLY_MASK (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  n2mask (struct in6_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nat64lsn_apply_mask(int af, void *prefix, uint16_t plen)
{
	struct in6_addr mask6, *p6;
	struct in_addr mask4, *p4;

	if (af == AF_INET) {
		p4 = (struct in_addr *)prefix;
		mask4.s_addr = htonl(~((1 << (32 - plen)) - 1));
		p4->s_addr &= mask4.s_addr;
	} else if (af == AF_INET6) {
		p6 = (struct in6_addr *)prefix;
		n2mask(&mask6, plen);
		APPLY_MASK(p6, &mask6);
	}
}