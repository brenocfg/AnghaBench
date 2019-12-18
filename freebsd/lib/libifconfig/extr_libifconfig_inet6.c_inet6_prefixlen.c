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
struct TYPE_2__ {int /*<<< orphan*/ * __u6_addr32; } ;
struct in6_addr {TYPE_1__ __u6_addr; } ;

/* Variables and functions */
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inet6_prefixlen(struct in6_addr *addr)
{
	int prefixlen = 0;
	int i;

	for (i = 0; i < 4; i++) {
		int x = ffs(ntohl(addr->__u6_addr.__u6_addr32[i]));
		prefixlen += x == 0 ? 0 : 33 - x;
		if (x != 1) {
			break;
		}
	}
	return (prefixlen);
}