#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* __u6_addr8; } ;
struct in6_addr {TYPE_1__ __u6_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_WKPFX (struct in6_addr const*) ; 
 scalar_t__ nat64_check_prefixlen (int) ; 

int
nat64_check_prefix6(const struct in6_addr *prefix, int length)
{

	if (nat64_check_prefixlen(length) != 0)
		return (EINVAL);

	/* Well-known prefix has 96 prefix length */
	if (IN6_IS_ADDR_WKPFX(prefix) && length != 96)
		return (EINVAL);

	/* Bits 64 to 71 must be set to zero */
	if (prefix->__u6_addr.__u6_addr8[8] != 0)
		return (EINVAL);

	/* Some extra checks */
	if (IN6_IS_ADDR_MULTICAST(prefix) ||
	    IN6_IS_ADDR_UNSPECIFIED(prefix) ||
	    IN6_IS_ADDR_LOOPBACK(prefix))
		return (EINVAL);
	return (0);
}