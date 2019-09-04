#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  map; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_treebuilder ;
struct TYPE_11__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  filename; scalar_t__ oid; } ;
typedef  TYPE_2__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_filemode_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_TREE ; 
 TYPE_2__* alloc_entry (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int check_entry (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_2__* git_strmap_get (int /*<<< orphan*/ ,char const*) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_tree_entry_free (TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_treebuilder_insert(
	const git_tree_entry **entry_out,
	git_treebuilder *bld,
	const char *filename,
	const git_oid *id,
	git_filemode_t filemode)
{
	git_tree_entry *entry;
	int error;

	assert(bld && id && filename);

	if ((error = check_entry(bld->repo, filename, id, filemode)) < 0)
		return error;

	if ((entry = git_strmap_get(bld->map, filename)) != NULL) {
		git_oid_cpy((git_oid *) entry->oid, id);
	} else {
		entry = alloc_entry(filename, strlen(filename), id);
		GIT_ERROR_CHECK_ALLOC(entry);

		if ((error = git_strmap_set(bld->map, entry->filename, entry)) < 0) {
			git_tree_entry_free(entry);
			git_error_set(GIT_ERROR_TREE, "failed to insert %s", filename);
			return -1;
		}
	}

	entry->attr = filemode;

	if (entry_out)
		*entry_out = entry;

	return 0;
}