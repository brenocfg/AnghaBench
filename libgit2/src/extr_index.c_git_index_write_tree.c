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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/ * INDEX_OWNER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int create_index_error (int,char*) ; 
 int git_tree__write_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_index_write_tree(git_oid *oid, git_index *index)
{
	git_repository *repo;

	assert(oid && index);

	repo = INDEX_OWNER(index);

	if (repo == NULL)
		return create_index_error(-1, "Failed to write tree. "
		  "the index file is not backed up by an existing repository");

	return git_tree__write_index(oid, index, repo);
}