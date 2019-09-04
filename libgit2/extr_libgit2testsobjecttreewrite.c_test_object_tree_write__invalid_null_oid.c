#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_treebuilder ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
struct TYPE_7__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_4__* git_error_last () ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void test_object_tree_write__invalid_null_oid(void)
{
	git_treebuilder *bld;
	git_oid null_oid = {{0}};

	cl_git_pass(git_treebuilder_new(&bld, g_repo, NULL));
	cl_git_fail(git_treebuilder_insert(NULL, bld, "null_oid_file", &null_oid, GIT_FILEMODE_BLOB));
	cl_assert(git_error_last() && strstr(git_error_last()->message, "null OID") != NULL);

	git_treebuilder_free(bld);
}