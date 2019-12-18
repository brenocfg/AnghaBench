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
struct pf_rule_addr {scalar_t__ neg; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
addrs_equal(struct pf_rule_addr *a, struct pf_rule_addr *b)
{
	if (a->neg != b->neg)
		return (0);
	return (memcmp(&a->addr, &b->addr, sizeof(a->addr)) == 0);
}