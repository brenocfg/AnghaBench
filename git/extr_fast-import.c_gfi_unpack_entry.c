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
struct packed_git {scalar_t__ pack_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct object_entry {size_t pack_id; TYPE_1__ idx; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 struct packed_git** all_packs ; 
 int /*<<< orphan*/  close_pack_windows (struct packed_git*) ; 
 int /*<<< orphan*/  hashflush (int /*<<< orphan*/ ) ; 
 struct packed_git* pack_data ; 
 int /*<<< orphan*/  pack_file ; 
 scalar_t__ pack_size ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 void* unpack_entry (int /*<<< orphan*/ ,struct packed_git*,int /*<<< orphan*/ ,int*,unsigned long*) ; 

__attribute__((used)) static void *gfi_unpack_entry(
	struct object_entry *oe,
	unsigned long *sizep)
{
	enum object_type type;
	struct packed_git *p = all_packs[oe->pack_id];
	if (p == pack_data && p->pack_size < (pack_size + the_hash_algo->rawsz)) {
		/* The object is stored in the packfile we are writing to
		 * and we have modified it since the last time we scanned
		 * back to read a previously written object.  If an old
		 * window covered [p->pack_size, p->pack_size + rawsz) its
		 * data is stale and is not valid.  Closing all windows
		 * and updating the packfile length ensures we can read
		 * the newly written data.
		 */
		close_pack_windows(p);
		hashflush(pack_file);

		/* We have to offer rawsz bytes additional on the end of
		 * the packfile as the core unpacker code assumes the
		 * footer is present at the file end and must promise
		 * at least rawsz bytes within any window it maps.  But
		 * we don't actually create the footer here.
		 */
		p->pack_size = pack_size + the_hash_algo->rawsz;
	}
	return unpack_entry(the_repository, p, oe->idx.offset, &type, sizep);
}