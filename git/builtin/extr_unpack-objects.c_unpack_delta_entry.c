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
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  int off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int rawsz; } ;

/* Variables and functions */
 scalar_t__ MSB (int,int) ; 
 int OBJ_REF_DELTA ; 
 int /*<<< orphan*/  add_delta_to_list (unsigned int,struct object_id*,int,void*,unsigned long) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ dry_run ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 unsigned char* fill (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* get_data (unsigned long) ; 
 int has_errors ; 
 scalar_t__ has_object_file (struct object_id*) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  is_null_oid (struct object_id*) ; 
 struct object_id null_oid ; 
 TYPE_2__* obj_list ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 void* read_object_file (struct object_id*,int*,unsigned long*) ; 
 int /*<<< orphan*/  recover ; 
 scalar_t__ resolve_against_held (unsigned int,struct object_id*,void*,unsigned long) ; 
 int /*<<< orphan*/  resolve_delta (unsigned int,int,void*,unsigned long,void*,unsigned long) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  use (int) ; 

__attribute__((used)) static void unpack_delta_entry(enum object_type type, unsigned long delta_size,
			       unsigned nr)
{
	void *delta_data, *base;
	unsigned long base_size;
	struct object_id base_oid;

	if (type == OBJ_REF_DELTA) {
		hashcpy(base_oid.hash, fill(the_hash_algo->rawsz));
		use(the_hash_algo->rawsz);
		delta_data = get_data(delta_size);
		if (dry_run || !delta_data) {
			free(delta_data);
			return;
		}
		if (has_object_file(&base_oid))
			; /* Ok we have this one */
		else if (resolve_against_held(nr, &base_oid,
					      delta_data, delta_size))
			return; /* we are done */
		else {
			/* cannot resolve yet --- queue it */
			oidclr(&obj_list[nr].oid);
			add_delta_to_list(nr, &base_oid, 0, delta_data, delta_size);
			return;
		}
	} else {
		unsigned base_found = 0;
		unsigned char *pack, c;
		off_t base_offset;
		unsigned lo, mid, hi;

		pack = fill(1);
		c = *pack;
		use(1);
		base_offset = c & 127;
		while (c & 128) {
			base_offset += 1;
			if (!base_offset || MSB(base_offset, 7))
				die("offset value overflow for delta base object");
			pack = fill(1);
			c = *pack;
			use(1);
			base_offset = (base_offset << 7) + (c & 127);
		}
		base_offset = obj_list[nr].offset - base_offset;
		if (base_offset <= 0 || base_offset >= obj_list[nr].offset)
			die("offset value out of bound for delta base object");

		delta_data = get_data(delta_size);
		if (dry_run || !delta_data) {
			free(delta_data);
			return;
		}
		lo = 0;
		hi = nr;
		while (lo < hi) {
			mid = lo + (hi - lo) / 2;
			if (base_offset < obj_list[mid].offset) {
				hi = mid;
			} else if (base_offset > obj_list[mid].offset) {
				lo = mid + 1;
			} else {
				oidcpy(&base_oid, &obj_list[mid].oid);
				base_found = !is_null_oid(&base_oid);
				break;
			}
		}
		if (!base_found) {
			/*
			 * The delta base object is itself a delta that
			 * has not been resolved yet.
			 */
			oidclr(&obj_list[nr].oid);
			add_delta_to_list(nr, &null_oid, base_offset, delta_data, delta_size);
			return;
		}
	}

	if (resolve_against_held(nr, &base_oid, delta_data, delta_size))
		return;

	base = read_object_file(&base_oid, &type, &base_size);
	if (!base) {
		error("failed to read delta-pack base object %s",
		      oid_to_hex(&base_oid));
		if (!recover)
			exit(1);
		has_errors = 1;
		return;
	}
	resolve_delta(nr, type, base, base_size, delta_data, delta_size);
	free(base);
}