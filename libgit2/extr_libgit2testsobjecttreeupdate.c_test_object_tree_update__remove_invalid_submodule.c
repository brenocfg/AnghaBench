#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {TYPE_2__ member_0; } ;
struct TYPE_7__ {char* member_3; int /*<<< orphan*/  member_2; TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ git_tree_update ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_TREE_UPDATE_REMOVE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_create_updated (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_object_tree_update__remove_invalid_submodule(void)
{
	git_tree *baseline;
	git_oid updated_tree_id, baseline_id;
	git_tree_update updates[] = {
		{GIT_TREE_UPDATE_REMOVE, {{0}}, GIT_FILEMODE_BLOB, "submodule"},
	};

	/* This tree contains a submodule with an all-zero commit for a submodule named 'submodule' */
	cl_git_pass(git_oid_fromstr(&baseline_id, "396c7f1adb7925f51ba13a75f48252f44c5a14a2"));
	cl_git_pass(git_tree_lookup(&baseline, g_repo, &baseline_id));
	cl_git_pass(git_tree_create_updated(&updated_tree_id, g_repo, baseline, 1, updates));

	git_tree_free(baseline);
}