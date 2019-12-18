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
addr_is_all0s(const struct xaddr *a)
{
	int i;

	switch (a->af) {
	case AF_INET:
		return (a->v4.s_addr == 0 ? 0 : -1);
	case AF_INET6:;
		for (i = 0; i < 4; i++)
			if (a->addr32[i] != 0)
				return (-1);
		return (0);
	default:
		return (-1);
	}
}