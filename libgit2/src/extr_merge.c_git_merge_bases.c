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
typedef  int /*<<< orphan*/  git_oidarray ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__* item; } ;
typedef  TYPE_2__ git_commit_list ;
typedef  int /*<<< orphan*/  git_array_oid_t ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_array_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_list_free (TYPE_2__**) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidarray__from_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int merge_bases (TYPE_2__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int git_merge_bases(git_oidarray *out, git_repository *repo, const git_oid *one, const git_oid *two)
{
	int error;
	git_revwalk *walk;
	git_commit_list *result, *list;
	git_array_oid_t array;

	git_array_init(array);

	if ((error = merge_bases(&result, &walk, repo, one, two)) < 0)
		return error;

	list = result;
	while (list) {
		git_oid *id = git_array_alloc(array);
		if (id == NULL)
			goto on_error;

		git_oid_cpy(id, &list->item->oid);
		list = list->next;
	}

	git_oidarray__from_array(out, &array);
	git_commit_list_free(&result);
	git_revwalk_free(walk);

	return 0;

on_error:
	git_commit_list_free(&result);
	git_revwalk_free(walk);
	return -1;
}