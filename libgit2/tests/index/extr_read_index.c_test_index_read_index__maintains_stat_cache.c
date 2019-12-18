#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {size_t seconds; } ;
struct TYPE_7__ {size_t seconds; } ;
struct TYPE_9__ {char* path; int file_size; int mode; TYPE_2__ mtime; TYPE_1__ ctime; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/ * _index ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 size_t git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_read_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

void test_index_read_index__maintains_stat_cache(void)
{
	git_index *new_index;
	git_oid index_id;
	git_index_entry new_entry;
	const git_index_entry *e;
	git_tree *tree;
	size_t i;

	cl_assert_equal_i(4, git_index_entrycount(_index));

	/* write-tree */
	cl_git_pass(git_index_write_tree(&index_id, _index));

	/* read-tree, then read index */
	git_tree_lookup(&tree, _repo, &index_id);
	cl_git_pass(git_index_new(&new_index));
	cl_git_pass(git_index_read_tree(new_index, tree));
	git_tree_free(tree);

	/* add a new entry that will not have stat data */
	memset(&new_entry, 0, sizeof(git_index_entry));
	new_entry.path = "Hello";
	git_oid_fromstr(&new_entry.id, "0123456789012345678901234567890123456789");
	new_entry.file_size = 1234;
	new_entry.mode = 0100644;
	cl_git_pass(git_index_add(new_index, &new_entry));
	cl_assert_equal_i(5, git_index_entrycount(new_index));

	cl_git_pass(git_index_read_index(_index, new_index));
	git_index_free(new_index);

	cl_assert_equal_i(5, git_index_entrycount(_index));

	for (i = 0; i < git_index_entrycount(_index); i++) {
		e = git_index_get_byindex(_index, i);

		if (strcmp(e->path, "Hello") == 0) {
			cl_assert_equal_i(0, e->ctime.seconds);
			cl_assert_equal_i(0, e->mtime.seconds);
		} else {
			cl_assert(0 != e->ctime.seconds);
			cl_assert(0 != e->mtime.seconds);
		}
	}
}