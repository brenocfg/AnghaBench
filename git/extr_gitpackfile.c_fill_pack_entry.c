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
struct packed_git {unsigned int num_bad_objects; scalar_t__ bad_object_sha1; } ;
struct pack_entry {struct packed_git* p; scalar_t__ offset; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 scalar_t__ find_pack_entry_one (int /*<<< orphan*/ ,struct packed_git*) ; 
 scalar_t__ hasheq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  is_pack_valid (struct packed_git*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int fill_pack_entry(const struct object_id *oid,
			   struct pack_entry *e,
			   struct packed_git *p)
{
	off_t offset;

	if (p->num_bad_objects) {
		unsigned i;
		for (i = 0; i < p->num_bad_objects; i++)
			if (hasheq(oid->hash,
				   p->bad_object_sha1 + the_hash_algo->rawsz * i))
				return 0;
	}

	offset = find_pack_entry_one(oid->hash, p);
	if (!offset)
		return 0;

	/*
	 * We are about to tell the caller where they can locate the
	 * requested object.  We better make sure the packfile is
	 * still here and can be accessed before supplying that
	 * answer, as it may have been deleted since the index was
	 * loaded!
	 */
	if (!is_pack_valid(p))
		return 0;
	e->offset = offset;
	e->p = p;
	return 1;
}