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
typedef  scalar_t__ uint32_t ;
struct pack_midx_entry {scalar_t__ pack_mtime; int /*<<< orphan*/  offset; int /*<<< orphan*/  pack_int_id; int /*<<< orphan*/  oid; } ;
struct multi_pack_index {scalar_t__ num_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  nth_midxed_object_oid (int /*<<< orphan*/ *,struct multi_pack_index*,scalar_t__) ; 
 int /*<<< orphan*/  nth_midxed_offset (struct multi_pack_index*,scalar_t__) ; 
 int /*<<< orphan*/  nth_midxed_pack_int_id (struct multi_pack_index*,scalar_t__) ; 

__attribute__((used)) static int nth_midxed_pack_midx_entry(struct multi_pack_index *m,
				      struct pack_midx_entry *e,
				      uint32_t pos)
{
	if (pos >= m->num_objects)
		return 1;

	nth_midxed_object_oid(&e->oid, m, pos);
	e->pack_int_id = nth_midxed_pack_int_id(m, pos);
	e->offset = nth_midxed_offset(m, pos);

	/* consider objects in midx to be from "old" packs */
	e->pack_mtime = 0;
	return 0;
}