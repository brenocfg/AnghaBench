#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  new_entries; int /*<<< orphan*/ * old_entries; int /*<<< orphan*/  entry_cmp; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ read_tree_data ;
struct TYPE_19__ {scalar_t__ attr; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ git_tree_entry ;
struct TYPE_20__ {scalar_t__ mode; scalar_t__ flags_extended; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_index_entry ;
struct TYPE_21__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 TYPE_4__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  INDEX_OWNER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_4__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_tree_entry__is_tree (TYPE_2__ const*) ; 
 int /*<<< orphan*/  git_tree_entry_id (TYPE_2__ const*) ; 
 TYPE_3__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  index_entry_adjust_namemask (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_entry_cpy (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ index_entry_create (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_3__*) ; 
 int /*<<< orphan*/  index_find_in_entries (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_tree_cb(
	const char *root, const git_tree_entry *tentry, void *payload)
{
	read_tree_data *data = payload;
	git_index_entry *entry = NULL, *old_entry;
	git_buf path = GIT_BUF_INIT;
	size_t pos;

	if (git_tree_entry__is_tree(tentry))
		return 0;

	if (git_buf_joinpath(&path, root, tentry->filename) < 0)
		return -1;

	if (index_entry_create(&entry, INDEX_OWNER(data->index), path.ptr, NULL, false) < 0)
		return -1;

	entry->mode = tentry->attr;
	git_oid_cpy(&entry->id, git_tree_entry_id(tentry));

	/* look for corresponding old entry and copy data to new entry */
	if (data->old_entries != NULL &&
		!index_find_in_entries(
			&pos, data->old_entries, data->entry_cmp, path.ptr, 0, 0) &&
		(old_entry = git_vector_get(data->old_entries, pos)) != NULL &&
		entry->mode == old_entry->mode &&
		git_oid_equal(&entry->id, &old_entry->id))
	{
		index_entry_cpy(entry, old_entry);
		entry->flags_extended = 0;
	}

	index_entry_adjust_namemask(entry, path.size);
	git_buf_dispose(&path);

	if (git_vector_insert(data->new_entries, entry) < 0) {
		index_entry_free(entry);
		return -1;
	}

	return 0;
}