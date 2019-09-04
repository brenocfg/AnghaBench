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
struct object_info {unsigned long* sizep; int* typep; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct object_entry {int delta_idx; unsigned int delta_child_idx; unsigned int delta_sibling_idx; TYPE_1__ idx; int /*<<< orphan*/  in_pack_offset; scalar_t__ depth; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {struct object_entry* objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_PACK (struct object_entry*) ; 
 struct object_info OBJECT_INFO_INIT ; 
 int /*<<< orphan*/  SET_DELTA (struct object_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SIZE (struct object_entry*,unsigned long) ; 
 int /*<<< orphan*/  oe_set_type (struct object_entry*,int) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ packed_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_info*) ; 
 int /*<<< orphan*/  the_repository ; 
 TYPE_2__ to_pack ; 

__attribute__((used)) static void drop_reused_delta(struct object_entry *entry)
{
	unsigned *idx = &to_pack.objects[entry->delta_idx - 1].delta_child_idx;
	struct object_info oi = OBJECT_INFO_INIT;
	enum object_type type;
	unsigned long size;

	while (*idx) {
		struct object_entry *oe = &to_pack.objects[*idx - 1];

		if (oe == entry)
			*idx = oe->delta_sibling_idx;
		else
			idx = &oe->delta_sibling_idx;
	}
	SET_DELTA(entry, NULL);
	entry->depth = 0;

	oi.sizep = &size;
	oi.typep = &type;
	if (packed_object_info(the_repository, IN_PACK(entry), entry->in_pack_offset, &oi) < 0) {
		/*
		 * We failed to get the info from this pack for some reason;
		 * fall back to oid_object_info, which may find another copy.
		 * And if that fails, the error will be recorded in oe_type(entry)
		 * and dealt with in prepare_pack().
		 */
		oe_set_type(entry,
			    oid_object_info(the_repository, &entry->idx.oid, &size));
	} else {
		oe_set_type(entry, type);
	}
	SET_SIZE(entry, size);
}