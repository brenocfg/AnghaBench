#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_strmap ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_8__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_SUBMODULE_STATUS__HEAD_NOT_SUBMODULE ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_submodule_names (int /*<<< orphan*/ *) ; 
 int git_iterator_advance (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 void* git_strmap_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_submodule_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_owner (int /*<<< orphan*/ *) ; 
 int load_submodule_names (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submodule_get_or_create (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  submodule_update_from_head_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submodules_from_head(git_strmap *map, git_tree *head, git_config *cfg)
{
	int error;
	git_iterator *i = NULL;
	const git_index_entry *entry;
	git_strmap *names;

	if ((error = load_submodule_names(&names, git_tree_owner(head), cfg)))
		goto done;

	if ((error = git_iterator_for_tree(&i, head, NULL)) < 0)
		goto done;

	while (!(error = git_iterator_advance(&entry, i))) {
		git_submodule *sm;

		if ((sm = git_strmap_get(map, entry->path)) != NULL) {
			if (S_ISGITLINK(entry->mode))
				submodule_update_from_head_data(sm, entry->mode, &entry->id);
			else
				sm->flags |= GIT_SUBMODULE_STATUS__HEAD_NOT_SUBMODULE;
		} else if (S_ISGITLINK(entry->mode)) {
			const char *name;

			if ((name = git_strmap_get(names, entry->path)) == NULL)
				name = entry->path;

			if (!submodule_get_or_create(&sm, git_tree_owner(head), map, name)) {
				submodule_update_from_head_data(
					sm, entry->mode, &entry->id);
				git_submodule_free(sm);
			}
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

done:
	git_iterator_free(i);
	free_submodule_names(names);

	return error;
}