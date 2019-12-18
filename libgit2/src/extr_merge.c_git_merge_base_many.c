#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {TYPE_1__* item; } ;
typedef  TYPE_2__ git_commit_list ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_list_free (TYPE_2__**) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int merge_bases_many (TYPE_2__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 

int git_merge_base_many(git_oid *out, git_repository *repo, size_t length, const git_oid input_array[])
{
	git_revwalk *walk;
	git_commit_list *result = NULL;
	int error = 0;

	assert(out && repo && input_array);

	if ((error = merge_bases_many(&result, &walk, repo, length, input_array)) < 0)
		return error;

	git_oid_cpy(out, &result->item->oid);

	git_commit_list_free(&result);
	git_revwalk_free(walk);

	return 0;
}