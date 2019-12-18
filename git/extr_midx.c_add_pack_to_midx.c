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
struct pack_list {int nr; TYPE_1__* info; int /*<<< orphan*/  alloc; scalar_t__ m; int /*<<< orphan*/  pack_paths_checked; int /*<<< orphan*/  progress; } ;
struct TYPE_2__ {size_t orig_pack_int_id; scalar_t__ expired; int /*<<< orphan*/  pack_name; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_packed_git (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_pack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 scalar_t__ midx_contains_pack (scalar_t__,char const*) ; 
 scalar_t__ open_pack_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_pack_to_midx(const char *full_path, size_t full_path_len,
			     const char *file_name, void *data)
{
	struct pack_list *packs = (struct pack_list *)data;

	if (ends_with(file_name, ".idx")) {
		display_progress(packs->progress, ++packs->pack_paths_checked);
		if (packs->m && midx_contains_pack(packs->m, file_name))
			return;

		ALLOC_GROW(packs->info, packs->nr + 1, packs->alloc);

		packs->info[packs->nr].p = add_packed_git(full_path,
							  full_path_len,
							  0);

		if (!packs->info[packs->nr].p) {
			warning(_("failed to add packfile '%s'"),
				full_path);
			return;
		}

		if (open_pack_index(packs->info[packs->nr].p)) {
			warning(_("failed to open pack-index '%s'"),
				full_path);
			close_pack(packs->info[packs->nr].p);
			FREE_AND_NULL(packs->info[packs->nr].p);
			return;
		}

		packs->info[packs->nr].pack_name = xstrdup(file_name);
		packs->info[packs->nr].orig_pack_int_id = packs->nr;
		packs->info[packs->nr].expired = 0;
		packs->nr++;
	}
}