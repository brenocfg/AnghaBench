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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_array_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_list_free (TYPE_2__**) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidarray__from_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int merge_bases_many (TYPE_2__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 

int git_merge_bases_many(git_oidarray *out, git_repository *repo, size_t length, const git_oid input_array[])
{
	git_revwalk *walk;
	git_commit_list *list, *result = NULL;
	int error = 0;
	git_array_oid_t array;

	assert(out && repo && input_array);

	if ((error = merge_bases_many(&result, &walk, repo, length, input_array)) < 0)
		return error;

	git_array_init(array);

	list = result;
	while (list) {
		git_oid *id = git_array_alloc(array);
		if (id == NULL) {
			error = -1;
			goto cleanup;
		}

		git_oid_cpy(id, &list->item->oid);
		list = list->next;
	}

	git_oidarray__from_array(out, &array);

cleanup:
	git_commit_list_free(&result);
	git_revwalk_free(walk);

	return error;
}