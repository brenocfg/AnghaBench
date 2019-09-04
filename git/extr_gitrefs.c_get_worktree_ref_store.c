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
struct worktree {char* id; scalar_t__ is_current; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_ALL_CAPS ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 struct ref_store* get_main_ref_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_common_path (char*,char*) ; 
 struct ref_store* lookup_ref_store_map (int /*<<< orphan*/ *,char const*) ; 
 struct ref_store* ref_store_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_ref_store_map (int /*<<< orphan*/ *,char*,struct ref_store*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  worktree_ref_stores ; 

struct ref_store *get_worktree_ref_store(const struct worktree *wt)
{
	struct ref_store *refs;
	const char *id;

	if (wt->is_current)
		return get_main_ref_store(the_repository);

	id = wt->id ? wt->id : "/";
	refs = lookup_ref_store_map(&worktree_ref_stores, id);
	if (refs)
		return refs;

	if (wt->id)
		refs = ref_store_init(git_common_path("worktrees/%s", wt->id),
				      REF_STORE_ALL_CAPS);
	else
		refs = ref_store_init(get_git_common_dir(),
				      REF_STORE_ALL_CAPS);

	if (refs)
		register_ref_store_map(&worktree_ref_stores, "worktree",
				       refs, id);
	return refs;
}