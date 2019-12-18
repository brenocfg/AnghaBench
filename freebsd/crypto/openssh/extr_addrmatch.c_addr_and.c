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
struct xaddr {int af; int /*<<< orphan*/ * addr32; int /*<<< orphan*/  scope_id; TYPE_1__ v4; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (struct xaddr*,struct xaddr const*,int) ; 

__attribute__((used)) static int
addr_and(struct xaddr *dst, const struct xaddr *a, const struct xaddr *b)
{
	int i;

	if (dst == NULL || a == NULL || b == NULL || a->af != b->af)
		return -1;

	memcpy(dst, a, sizeof(*dst));
	switch (a->af) {
	case AF_INET:
		dst->v4.s_addr &= b->v4.s_addr;
		return 0;
	case AF_INET6:
		dst->scope_id = a->scope_id;
		for (i = 0; i < 4; i++)
			dst->addr32[i] &= b->addr32[i];
		return 0;
	default:
		return -1;
	}
}