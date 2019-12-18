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
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ WRITE_BITMAP_QUIET ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_object_entry (struct object_id const*,int,int /*<<< orphan*/ ,int,int,struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ have_duplicate_entry (struct object_id const*,int) ; 
 int /*<<< orphan*/  no_closure_warning ; 
 scalar_t__ no_try_delta (char const*) ; 
 int /*<<< orphan*/  nr_seen ; 
 int /*<<< orphan*/  pack_name_hash (char const*) ; 
 int /*<<< orphan*/  progress_state ; 
 int /*<<< orphan*/  want_object_in_pack (struct object_id const*,int,struct packed_git**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 
 scalar_t__ write_bitmap_index ; 

__attribute__((used)) static int add_object_entry(const struct object_id *oid, enum object_type type,
			    const char *name, int exclude)
{
	struct packed_git *found_pack = NULL;
	off_t found_offset = 0;

	display_progress(progress_state, ++nr_seen);

	if (have_duplicate_entry(oid, exclude))
		return 0;

	if (!want_object_in_pack(oid, exclude, &found_pack, &found_offset)) {
		/* The pack is missing an object, so it will not have closure */
		if (write_bitmap_index) {
			if (write_bitmap_index != WRITE_BITMAP_QUIET)
				warning(_(no_closure_warning));
			write_bitmap_index = 0;
		}
		return 0;
	}

	create_object_entry(oid, type, pack_name_hash(name),
			    exclude, name && no_try_delta(name),
			    found_pack, found_offset);
	return 1;
}