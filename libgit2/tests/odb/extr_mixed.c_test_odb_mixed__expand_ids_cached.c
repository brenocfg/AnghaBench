#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_odb_object ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  length; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_odb_expand_id ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  assert_found_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_odb_expand_ids (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_prefix_query (TYPE_1__**,size_t*) ; 

void test_odb_mixed__expand_ids_cached(void)
{
	git_odb_expand_id *ids;
	size_t i, num;

	/* test looking for the actual (correct) types after accessing the object */

	setup_prefix_query(&ids, &num);

	for (i = 0; i < num; i++) {
		git_odb_object *obj;
		if (ids[i].type == GIT_OBJECT_ANY)
			continue;
		cl_git_pass(git_odb_read_prefix(&obj, _odb, &ids[i].id, ids[i].length));
		git_odb_object_free(obj);
	}

	cl_git_pass(git_odb_expand_ids(_odb, ids, num));
	assert_found_objects(ids);
	git__free(ids);
}