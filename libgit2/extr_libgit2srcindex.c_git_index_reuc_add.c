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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index_reuc_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  index_entry_reuc_free (int /*<<< orphan*/ *) ; 
 int index_entry_reuc_init (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int index_reuc_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_index_reuc_add(git_index *index, const char *path,
	int ancestor_mode, const git_oid *ancestor_oid,
	int our_mode, const git_oid *our_oid,
	int their_mode, const git_oid *their_oid)
{
	git_index_reuc_entry *reuc = NULL;
	int error = 0;

	assert(index && path);

	if ((error = index_entry_reuc_init(&reuc, path, ancestor_mode,
			ancestor_oid, our_mode, our_oid, their_mode, their_oid)) < 0 ||
		(error = index_reuc_insert(index, reuc)) < 0)
		index_entry_reuc_free(reuc);

	return error;
}