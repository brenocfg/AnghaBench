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
struct pack_list {int nr; int /*<<< orphan*/  pack_name_concat_len; int /*<<< orphan*/ * names; int /*<<< orphan*/ * list; int /*<<< orphan*/  alloc_names; int /*<<< orphan*/  alloc_list; scalar_t__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_packed_git (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_pack (int /*<<< orphan*/ ) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 scalar_t__ midx_contains_pack (scalar_t__,char const*) ; 
 scalar_t__ open_pack_index (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_pack_to_midx(const char *full_path, size_t full_path_len,
			     const char *file_name, void *data)
{
	struct pack_list *packs = (struct pack_list *)data;

	if (ends_with(file_name, ".idx")) {
		if (packs->m && midx_contains_pack(packs->m, file_name))
			return;

		ALLOC_GROW(packs->list, packs->nr + 1, packs->alloc_list);
		ALLOC_GROW(packs->names, packs->nr + 1, packs->alloc_names);

		packs->list[packs->nr] = add_packed_git(full_path,
							full_path_len,
							0);

		if (!packs->list[packs->nr]) {
			warning(_("failed to add packfile '%s'"),
				full_path);
			return;
		}

		if (open_pack_index(packs->list[packs->nr])) {
			warning(_("failed to open pack-index '%s'"),
				full_path);
			close_pack(packs->list[packs->nr]);
			FREE_AND_NULL(packs->list[packs->nr]);
			return;
		}

		packs->names[packs->nr] = xstrdup(file_name);
		packs->pack_name_concat_len += strlen(file_name) + 1;
		packs->nr++;
	}
}