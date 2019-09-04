#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ git_odb_expand_id ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_BLOB ; 
 scalar_t__ GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  assert_found_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_notfound_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_odb_expand_ids (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  setup_prefix_query (TYPE_1__**,size_t*) ; 

void test_odb_mixed__expand_ids(void)
{
	git_odb_expand_id *ids;
	size_t i, num;

	/* test looking for the actual (correct) types */

	setup_prefix_query(&ids, &num);
	cl_git_pass(git_odb_expand_ids(_odb, ids, num));
	assert_found_objects(ids);
	git__free(ids);

	/* test looking for an explicit `type == 0` */

	setup_prefix_query(&ids, &num);

	for (i = 0; i < num; i++)
		ids[i].type = 0;

	cl_git_pass(git_odb_expand_ids(_odb, ids, num));
	assert_found_objects(ids);
	git__free(ids);

	/* test looking for an explicit GIT_OBJECT_ANY */

	setup_prefix_query(&ids, &num);

	for (i = 0; i < num; i++)
		ids[i].type = GIT_OBJECT_ANY;

	cl_git_pass(git_odb_expand_ids(_odb, ids, num));
	assert_found_objects(ids);
	git__free(ids);

	/* test looking for the completely wrong type */

	setup_prefix_query(&ids, &num);

	for (i = 0; i < num; i++)
		ids[i].type = (ids[i].type == GIT_OBJECT_BLOB) ?
			GIT_OBJECT_TREE : GIT_OBJECT_BLOB;

	cl_git_pass(git_odb_expand_ids(_odb, ids, num));
	assert_notfound_objects(ids);
	git__free(ids);
}