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
struct TYPE_2__ {int /*<<< orphan*/ * __u6_addr8; } ;
struct in6_addr {TYPE_1__ __u6_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (struct in6_addr const*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (struct in6_addr const*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (struct in6_addr const*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_WKPFX (struct in6_addr const*) ; 

int
ipfw_check_nat64prefix(const struct in6_addr *prefix, int length)
{

	switch (length) {
	case 32:
	case 40:
	case 48:
	case 56:
	case 64:
		/* Well-known prefix has 96 prefix length */
		if (IN6_IS_ADDR_WKPFX(prefix))
			return (EINVAL);
		/* FALLTHROUGH */
	case 96:
		/* Bits 64 to 71 must be set to zero */
		if (prefix->__u6_addr.__u6_addr8[8] != 0)
			return (EINVAL);
		/* XXX: looks incorrect */
		if (IN6_IS_ADDR_MULTICAST(prefix) ||
		    IN6_IS_ADDR_UNSPECIFIED(prefix) ||
		    IN6_IS_ADDR_LOOPBACK(prefix))
			return (EINVAL);
		return (0);
	}
	return (EINVAL);
}