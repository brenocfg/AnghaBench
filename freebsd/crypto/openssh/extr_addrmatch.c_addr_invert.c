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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct xaddr {int af; int /*<<< orphan*/ * addr32; TYPE_1__ v4; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

__attribute__((used)) static int
addr_invert(struct xaddr *n)
{
	int i;

	if (n == NULL)
		return (-1);

	switch (n->af) {
	case AF_INET:
		n->v4.s_addr = ~n->v4.s_addr;
		return (0);
	case AF_INET6:
		for (i = 0; i < 4; i++)
			n->addr32[i] = ~n->addr32[i];
		return (0);
	default:
		return (-1);
	}
}