#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int* s6_addr; } ;
struct TYPE_4__ {TYPE_1__ v6; } ;
struct cidr {int prefix; TYPE_2__ addr; } ;

/* Variables and functions */
 struct cidr* cidr_clone (struct cidr*) ; 

__attribute__((used)) static bool cidr_network6(struct cidr *a)
{
	uint8_t i;
	struct cidr *n = cidr_clone(a);

	for (i = 0; i < (128 - n->prefix) / 8; i++)
		n->addr.v6.s6_addr[15-i] = 0;

	if ((128 - n->prefix) % 8)
		n->addr.v6.s6_addr[15-i] &= ~((1 << ((128 - n->prefix) % 8)) - 1);

	return true;
}