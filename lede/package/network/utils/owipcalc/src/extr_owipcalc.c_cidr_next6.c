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
typedef  size_t uint8_t ;
struct in6_addr {size_t* s6_addr; } ;
struct TYPE_2__ {struct in6_addr v6; } ;
struct cidr {int prefix; TYPE_1__ addr; } ;

/* Variables and functions */
 struct cidr* cidr_clone (struct cidr*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool cidr_next6(struct cidr *a, struct cidr *b)
{
	uint8_t idx, carry = 1, overflow = 0;
	struct cidr *n = cidr_clone(a);
	struct in6_addr *x = &n->addr.v6;

	if (b->prefix == 0)
	{
		fprintf(stderr, "overflow during 'next'\n");
		return false;
	}

	idx = (b->prefix - 1) / 8;

	do {
		overflow = !!((x->s6_addr[idx] + carry) >= 256);
		x->s6_addr[idx] += carry;
		carry = overflow;
	}
	while (idx-- > 0);

	if (carry)
	{
		fprintf(stderr, "overflow during 'next'\n");
		return false;
	}

	n->prefix = b->prefix;

	return true;
}