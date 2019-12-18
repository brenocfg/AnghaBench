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
struct xaddr {int af; int /*<<< orphan*/  scope_id; scalar_t__* addr8; TYPE_1__ v4; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
addr_cmp(const struct xaddr *a, const struct xaddr *b)
{
	int i;

	if (a->af != b->af)
		return a->af == AF_INET6 ? 1 : -1;

	switch (a->af) {
	case AF_INET:
		if (a->v4.s_addr == b->v4.s_addr)
			return 0;
		return ntohl(a->v4.s_addr) > ntohl(b->v4.s_addr) ? 1 : -1;
	case AF_INET6:
		for (i = 0; i < 16; i++)
			if (a->addr8[i] - b->addr8[i] != 0)
				return a->addr8[i] > b->addr8[i] ? 1 : -1;
		if (a->scope_id == b->scope_id)
			return 0;
		return a->scope_id > b->scope_id ? 1 : -1;
	default:
		return -1;
	}
}