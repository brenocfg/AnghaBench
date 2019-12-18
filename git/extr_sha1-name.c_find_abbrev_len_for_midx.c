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
typedef  int uint32_t ;
struct object_id {int dummy; } ;
struct multi_pack_index {int num_objects; } ;
struct min_abbrev_data {scalar_t__ cur_len; scalar_t__ init_len; struct object_id* oid; } ;

/* Variables and functions */
 int bsearch_midx (struct object_id const*,struct multi_pack_index*,int*) ; 
 int /*<<< orphan*/  extend_abbrev_len (struct object_id*,struct min_abbrev_data*) ; 
 scalar_t__ nth_midxed_object_oid (struct object_id*,struct multi_pack_index*,int) ; 

__attribute__((used)) static void find_abbrev_len_for_midx(struct multi_pack_index *m,
				     struct min_abbrev_data *mad)
{
	int match = 0;
	uint32_t num, first = 0;
	struct object_id oid;
	const struct object_id *mad_oid;

	if (!m->num_objects)
		return;

	num = m->num_objects;
	mad_oid = mad->oid;
	match = bsearch_midx(mad_oid, m, &first);

	/*
	 * first is now the position in the packfile where we would insert
	 * mad->hash if it does not exist (or the position of mad->hash if
	 * it does exist). Hence, we consider a maximum of two objects
	 * nearby for the abbreviation length.
	 */
	mad->init_len = 0;
	if (!match) {
		if (nth_midxed_object_oid(&oid, m, first))
			extend_abbrev_len(&oid, mad);
	} else if (first < num - 1) {
		if (nth_midxed_object_oid(&oid, m, first + 1))
			extend_abbrev_len(&oid, mad);
	}
	if (first > 0) {
		if (nth_midxed_object_oid(&oid, m, first - 1))
			extend_abbrev_len(&oid, mad);
	}
	mad->init_len = mad->cur_len;
}