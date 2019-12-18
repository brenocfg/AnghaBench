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
struct packed_git {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct object_entry {scalar_t__ in_pack_offset; TYPE_1__ idx; } ;

/* Variables and functions */
 struct packed_git* IN_PACK (struct object_entry const*) ; 
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pack_offset_sort(const void *_a, const void *_b)
{
	const struct object_entry *a = *(struct object_entry **)_a;
	const struct object_entry *b = *(struct object_entry **)_b;
	const struct packed_git *a_in_pack = IN_PACK(a);
	const struct packed_git *b_in_pack = IN_PACK(b);

	/* avoid filesystem trashing with loose objects */
	if (!a_in_pack && !b_in_pack)
		return oidcmp(&a->idx.oid, &b->idx.oid);

	if (a_in_pack < b_in_pack)
		return -1;
	if (a_in_pack > b_in_pack)
		return 1;
	return a->in_pack_offset < b->in_pack_offset ? -1 :
			(a->in_pack_offset > b->in_pack_offset);
}