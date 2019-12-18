#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  crc32; } ;
struct object_entry {scalar_t__ in_pack_type; TYPE_2__ idx; } ;
struct hashfile {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_1__ idx; } ;

/* Variables and functions */
 TYPE_3__* DELTA (struct object_entry*) ; 
 int /*<<< orphan*/  IN_PACK (struct object_entry*) ; 
 scalar_t__ OBJ_OFS_DELTA ; 
 scalar_t__ OBJ_REF_DELTA ; 
 int /*<<< orphan*/  crc32_begin (struct hashfile*) ; 
 int /*<<< orphan*/  crc32_end (struct hashfile*) ; 
 int /*<<< orphan*/  nr_written ; 
 scalar_t__ oe_type (struct object_entry*) ; 
 scalar_t__ pack_size_limit ; 
 int /*<<< orphan*/  pack_to_stdout ; 
 int /*<<< orphan*/  reuse_object ; 
 scalar_t__ write_no_reuse_object (struct hashfile*,struct object_entry*,unsigned long,int) ; 
 scalar_t__ write_reuse_object (struct hashfile*,struct object_entry*,unsigned long,int) ; 
 int /*<<< orphan*/  written ; 
 int /*<<< orphan*/  written_delta ; 

__attribute__((used)) static off_t write_object(struct hashfile *f,
			  struct object_entry *entry,
			  off_t write_offset)
{
	unsigned long limit;
	off_t len;
	int usable_delta, to_reuse;

	if (!pack_to_stdout)
		crc32_begin(f);

	/* apply size limit if limited packsize and not first object */
	if (!pack_size_limit || !nr_written)
		limit = 0;
	else if (pack_size_limit <= write_offset)
		/*
		 * the earlier object did not fit the limit; avoid
		 * mistaking this with unlimited (i.e. limit = 0).
		 */
		limit = 1;
	else
		limit = pack_size_limit - write_offset;

	if (!DELTA(entry))
		usable_delta = 0;	/* no delta */
	else if (!pack_size_limit)
	       usable_delta = 1;	/* unlimited packfile */
	else if (DELTA(entry)->idx.offset == (off_t)-1)
		usable_delta = 0;	/* base was written to another pack */
	else if (DELTA(entry)->idx.offset)
		usable_delta = 1;	/* base already exists in this pack */
	else
		usable_delta = 0;	/* base could end up in another pack */

	if (!reuse_object)
		to_reuse = 0;	/* explicit */
	else if (!IN_PACK(entry))
		to_reuse = 0;	/* can't reuse what we don't have */
	else if (oe_type(entry) == OBJ_REF_DELTA ||
		 oe_type(entry) == OBJ_OFS_DELTA)
				/* check_object() decided it for us ... */
		to_reuse = usable_delta;
				/* ... but pack split may override that */
	else if (oe_type(entry) != entry->in_pack_type)
		to_reuse = 0;	/* pack has delta which is unusable */
	else if (DELTA(entry))
		to_reuse = 0;	/* we want to pack afresh */
	else
		to_reuse = 1;	/* we have it in-pack undeltified,
				 * and we do not need to deltify it.
				 */

	if (!to_reuse)
		len = write_no_reuse_object(f, entry, limit, usable_delta);
	else
		len = write_reuse_object(f, entry, limit, usable_delta);
	if (!len)
		return 0;

	if (usable_delta)
		written_delta++;
	written++;
	if (!pack_to_stdout)
		entry->idx.crc32 = crc32_end(f);
	return len;
}