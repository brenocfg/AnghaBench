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
typedef  int /*<<< orphan*/  uint32_t ;
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  create_object_entry (struct object_id const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ have_duplicate_entry (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_seen ; 
 int /*<<< orphan*/  progress_state ; 
 int /*<<< orphan*/  want_object_in_pack (struct object_id const*,int /*<<< orphan*/ ,struct packed_git**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_object_entry_from_bitmap(const struct object_id *oid,
					enum object_type type,
					int flags, uint32_t name_hash,
					struct packed_git *pack, off_t offset)
{
	display_progress(progress_state, ++nr_seen);

	if (have_duplicate_entry(oid, 0))
		return 0;

	if (!want_object_in_pack(oid, 0, &pack, &offset))
		return 0;

	create_object_entry(oid, type, name_hash, 0, 0, pack, offset);
	return 1;
}