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
struct revindex_entry {int /*<<< orphan*/  nr; } ;
struct packed_git {int dummy; } ;
struct pack_window {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct object_entry {int in_pack_offset; int in_pack_type; unsigned long in_pack_header_size; scalar_t__ type_valid; TYPE_1__ idx; int /*<<< orphan*/  delta_child_idx; int /*<<< orphan*/  delta_sibling_idx; int /*<<< orphan*/  preferred_base; } ;
typedef  int off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {int /*<<< orphan*/  rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 struct packed_git* IN_PACK (struct object_entry*) ; 
 int /*<<< orphan*/  MSB (int,int) ; 
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
#define  OBJ_OFS_DELTA 129 
#define  OBJ_REF_DELTA 128 
 int /*<<< orphan*/  SET_DELTA (struct object_entry*,struct object_entry*) ; 
 int /*<<< orphan*/  SET_DELTA_CHILD (struct object_entry*,struct object_entry*) ; 
 int /*<<< orphan*/  SET_DELTA_EXT (struct object_entry*,unsigned char const*) ; 
 int /*<<< orphan*/  SET_DELTA_SIZE (struct object_entry*,unsigned long) ; 
 int /*<<< orphan*/  SET_SIZE (struct object_entry*,unsigned long) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ can_reuse_delta (unsigned char const*,struct object_entry*,struct object_entry**) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct revindex_entry* find_pack_revindex (struct packed_git*,int) ; 
 unsigned long get_size_from_delta (struct packed_git*,struct pack_window**,int) ; 
 unsigned char* nth_packed_object_sha1 (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oe_set_type (struct object_entry*,int) ; 
 scalar_t__ oe_type (struct object_entry*) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reuse_delta ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 unsigned long unpack_object_header_buffer (unsigned char*,unsigned long,int*,unsigned long*) ; 
 int /*<<< orphan*/  unuse_pack (struct pack_window**) ; 
 void* use_pack (struct packed_git*,struct pack_window**,int,unsigned long*) ; 

__attribute__((used)) static void check_object(struct object_entry *entry)
{
	unsigned long canonical_size;

	if (IN_PACK(entry)) {
		struct packed_git *p = IN_PACK(entry);
		struct pack_window *w_curs = NULL;
		const unsigned char *base_ref = NULL;
		struct object_entry *base_entry;
		unsigned long used, used_0;
		unsigned long avail;
		off_t ofs;
		unsigned char *buf, c;
		enum object_type type;
		unsigned long in_pack_size;

		buf = use_pack(p, &w_curs, entry->in_pack_offset, &avail);

		/*
		 * We want in_pack_type even if we do not reuse delta
		 * since non-delta representations could still be reused.
		 */
		used = unpack_object_header_buffer(buf, avail,
						   &type,
						   &in_pack_size);
		if (used == 0)
			goto give_up;

		if (type < 0)
			BUG("invalid type %d", type);
		entry->in_pack_type = type;

		/*
		 * Determine if this is a delta and if so whether we can
		 * reuse it or not.  Otherwise let's find out as cheaply as
		 * possible what the actual type and size for this object is.
		 */
		switch (entry->in_pack_type) {
		default:
			/* Not a delta hence we've already got all we need. */
			oe_set_type(entry, entry->in_pack_type);
			SET_SIZE(entry, in_pack_size);
			entry->in_pack_header_size = used;
			if (oe_type(entry) < OBJ_COMMIT || oe_type(entry) > OBJ_BLOB)
				goto give_up;
			unuse_pack(&w_curs);
			return;
		case OBJ_REF_DELTA:
			if (reuse_delta && !entry->preferred_base)
				base_ref = use_pack(p, &w_curs,
						entry->in_pack_offset + used, NULL);
			entry->in_pack_header_size = used + the_hash_algo->rawsz;
			break;
		case OBJ_OFS_DELTA:
			buf = use_pack(p, &w_curs,
				       entry->in_pack_offset + used, NULL);
			used_0 = 0;
			c = buf[used_0++];
			ofs = c & 127;
			while (c & 128) {
				ofs += 1;
				if (!ofs || MSB(ofs, 7)) {
					error(_("delta base offset overflow in pack for %s"),
					      oid_to_hex(&entry->idx.oid));
					goto give_up;
				}
				c = buf[used_0++];
				ofs = (ofs << 7) + (c & 127);
			}
			ofs = entry->in_pack_offset - ofs;
			if (ofs <= 0 || ofs >= entry->in_pack_offset) {
				error(_("delta base offset out of bound for %s"),
				      oid_to_hex(&entry->idx.oid));
				goto give_up;
			}
			if (reuse_delta && !entry->preferred_base) {
				struct revindex_entry *revidx;
				revidx = find_pack_revindex(p, ofs);
				if (!revidx)
					goto give_up;
				base_ref = nth_packed_object_sha1(p, revidx->nr);
			}
			entry->in_pack_header_size = used + used_0;
			break;
		}

		if (can_reuse_delta(base_ref, entry, &base_entry)) {
			oe_set_type(entry, entry->in_pack_type);
			SET_SIZE(entry, in_pack_size); /* delta size */
			SET_DELTA_SIZE(entry, in_pack_size);

			if (base_entry) {
				SET_DELTA(entry, base_entry);
				entry->delta_sibling_idx = base_entry->delta_child_idx;
				SET_DELTA_CHILD(base_entry, entry);
			} else {
				SET_DELTA_EXT(entry, base_ref);
			}

			unuse_pack(&w_curs);
			return;
		}

		if (oe_type(entry)) {
			off_t delta_pos;

			/*
			 * This must be a delta and we already know what the
			 * final object type is.  Let's extract the actual
			 * object size from the delta header.
			 */
			delta_pos = entry->in_pack_offset + entry->in_pack_header_size;
			canonical_size = get_size_from_delta(p, &w_curs, delta_pos);
			if (canonical_size == 0)
				goto give_up;
			SET_SIZE(entry, canonical_size);
			unuse_pack(&w_curs);
			return;
		}

		/*
		 * No choice but to fall back to the recursive delta walk
		 * with oid_object_info() to find about the object type
		 * at this point...
		 */
		give_up:
		unuse_pack(&w_curs);
	}

	oe_set_type(entry,
		    oid_object_info(the_repository, &entry->idx.oid, &canonical_size));
	if (entry->type_valid) {
		SET_SIZE(entry, canonical_size);
	} else {
		/*
		 * Bad object type is checked in prepare_pack().  This is
		 * to permit a missing preferred base object to be ignored
		 * as a preferred base.  Doing so can result in a larger
		 * pack file, but the transfer will still take place.
		 */
	}
}