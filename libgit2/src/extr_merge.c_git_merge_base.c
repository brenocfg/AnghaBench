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
 int /*<<< orphan*/  git_commit_list_free (TYPE_2__**) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int merge_bases (TYPE_2__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int git_merge_base(git_oid *out, git_repository *repo, const git_oid *one, const git_oid *two)
{
	int error;
	git_revwalk *walk;
	git_commit_list *result;

	if ((error = merge_bases(&result, &walk, repo, one, two)) < 0)
		return error;

	git_oid_cpy(out, &result->item->oid);
	git_commit_list_free(&result);
	git_revwalk_free(walk);

	return 0;
}