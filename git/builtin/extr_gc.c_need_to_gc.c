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
typedef  int uint64_t ;
struct string_list {scalar_t__ nr; } ;
struct packed_git {int dummy; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  add_repack_all_option (struct string_list*) ; 
 int /*<<< orphan*/  add_repack_incremental_option () ; 
 scalar_t__ big_pack_threshold ; 
 int estimate_repack_memory (struct packed_git*) ; 
 struct packed_git* find_base_packs (struct string_list*,scalar_t__) ; 
 scalar_t__ gc_auto_pack_limit ; 
 scalar_t__ gc_auto_threshold ; 
 scalar_t__ run_hook_le (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ too_many_loose_objects () ; 
 scalar_t__ too_many_packs () ; 
 int total_ram () ; 

__attribute__((used)) static int need_to_gc(void)
{
	/*
	 * Setting gc.auto to 0 or negative can disable the
	 * automatic gc.
	 */
	if (gc_auto_threshold <= 0)
		return 0;

	/*
	 * If there are too many loose objects, but not too many
	 * packs, we run "repack -d -l".  If there are too many packs,
	 * we run "repack -A -d -l".  Otherwise we tell the caller
	 * there is no need.
	 */
	if (too_many_packs()) {
		struct string_list keep_pack = STRING_LIST_INIT_NODUP;

		if (big_pack_threshold) {
			find_base_packs(&keep_pack, big_pack_threshold);
			if (keep_pack.nr >= gc_auto_pack_limit) {
				big_pack_threshold = 0;
				string_list_clear(&keep_pack, 0);
				find_base_packs(&keep_pack, 0);
			}
		} else {
			struct packed_git *p = find_base_packs(&keep_pack, 0);
			uint64_t mem_have, mem_want;

			mem_have = total_ram();
			mem_want = estimate_repack_memory(p);

			/*
			 * Only allow 1/2 of memory for pack-objects, leave
			 * the rest for the OS and other processes in the
			 * system.
			 */
			if (!mem_have || mem_want < mem_have / 2)
				string_list_clear(&keep_pack, 0);
		}

		add_repack_all_option(&keep_pack);
		string_list_clear(&keep_pack, 0);
	} else if (too_many_loose_objects())
		add_repack_incremental_option();
	else
		return 0;

	if (run_hook_le(NULL, "pre-auto-gc", NULL))
		return 0;
	return 1;
}