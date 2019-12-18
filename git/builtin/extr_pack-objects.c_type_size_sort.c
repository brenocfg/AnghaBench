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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct object_entry {scalar_t__ hash; scalar_t__ preferred_base; TYPE_1__ idx; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 unsigned long SIZE (struct object_entry const*) ; 
 int island_delta_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int oe_type (struct object_entry const*) ; 
 scalar_t__ use_delta_islands ; 

__attribute__((used)) static int type_size_sort(const void *_a, const void *_b)
{
	const struct object_entry *a = *(struct object_entry **)_a;
	const struct object_entry *b = *(struct object_entry **)_b;
	const enum object_type a_type = oe_type(a);
	const enum object_type b_type = oe_type(b);
	const unsigned long a_size = SIZE(a);
	const unsigned long b_size = SIZE(b);

	if (a_type > b_type)
		return -1;
	if (a_type < b_type)
		return 1;
	if (a->hash > b->hash)
		return -1;
	if (a->hash < b->hash)
		return 1;
	if (a->preferred_base > b->preferred_base)
		return -1;
	if (a->preferred_base < b->preferred_base)
		return 1;
	if (use_delta_islands) {
		const int island_cmp = island_delta_cmp(&a->idx.oid, &b->idx.oid);
		if (island_cmp)
			return island_cmp;
	}
	if (a_size > b_size)
		return -1;
	if (a_size < b_size)
		return 1;
	return a < b ? -1 : (a > b);  /* newest first */
}