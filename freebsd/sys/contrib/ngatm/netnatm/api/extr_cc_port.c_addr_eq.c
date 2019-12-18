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
struct uni_addr {scalar_t__ type; scalar_t__ plan; scalar_t__ len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __inline int
addr_eq(const struct uni_addr *a1, const struct uni_addr *a2)
{
	return (a1->type == a2->type && a1->plan == a2->plan &&
	    a1->len == a2->len && memcmp(a1->addr, a2->addr, a1->len) == 0);
}