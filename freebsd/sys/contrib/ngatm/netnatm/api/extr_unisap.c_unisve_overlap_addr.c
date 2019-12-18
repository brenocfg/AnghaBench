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
struct unisve_addr {scalar_t__ type; scalar_t__ plan; scalar_t__ len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_OVERLAP (struct unisve_addr const*,struct unisve_addr const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
unisve_overlap_addr(const struct unisve_addr *s1, const struct unisve_addr *s2)
{
	COMMON_OVERLAP(s1, s2);

	return (s1->type == s2->type && s1->plan == s2->plan &&
	    s1->len == s2->len && memcmp(s1->addr, s2->addr, s1->len) == 0);
}