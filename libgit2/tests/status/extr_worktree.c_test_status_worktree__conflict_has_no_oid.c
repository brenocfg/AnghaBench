#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_28__ {TYPE_8__* index_to_workdir; TYPE_5__* head_to_index; int /*<<< orphan*/  status; } ;
typedef  TYPE_9__ git_status_entry ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {TYPE_2__ member_0; } ;
typedef  TYPE_10__ git_oid ;
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int mode; char* path; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_11__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_26__ {int flags; scalar_t__ mode; scalar_t__ size; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct TYPE_25__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct TYPE_27__ {TYPE_7__ new_file; TYPE_6__ old_file; } ;
struct TYPE_23__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct TYPE_22__ {scalar_t__ mode; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct TYPE_24__ {TYPE_4__ new_file; TYPE_3__ old_file; } ;

/* Variables and functions */
 int GIT_DIFF_FLAG_VALID_ID ; 
 int GIT_STATUS_CONFLICTED ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ *,TYPE_11__*,TYPE_11__*,TYPE_11__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_equal (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_9__* git_status_byindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_status_worktree__conflict_has_no_oid(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_index *index;
	git_index_entry entry = {{0}};
	git_status_list *statuslist;
	const git_status_entry *status;
	git_oid zero_id = {{0}};

	entry.mode = 0100644;
	entry.path = "modified_file";
	git_oid_fromstr(&entry.id, "452e4244b5d083ddf0460acf1ecc74db9dcfa11a");

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_conflict_add(index, &entry, &entry, &entry));

	git_status_list_new(&statuslist, repo, NULL);

	cl_assert_equal_i(16, git_status_list_entrycount(statuslist));

	status = git_status_byindex(statuslist, 2);

	cl_assert_equal_i(GIT_STATUS_CONFLICTED, status->status);
	cl_assert_equal_s("modified_file", status->head_to_index->old_file.path);
	cl_assert(!git_oid_equal(&zero_id, &status->head_to_index->old_file.id));
	cl_assert(0 != status->head_to_index->old_file.mode);
	cl_assert_equal_s("modified_file", status->head_to_index->new_file.path);
	cl_assert_equal_oid(&zero_id, &status->head_to_index->new_file.id);
	cl_assert_equal_i(0, status->head_to_index->new_file.mode);
	cl_assert_equal_i(0, status->head_to_index->new_file.size);

	cl_assert_equal_s("modified_file", status->index_to_workdir->old_file.path);
	cl_assert_equal_oid(&zero_id, &status->index_to_workdir->old_file.id);
	cl_assert_equal_i(0, status->index_to_workdir->old_file.mode);
	cl_assert_equal_i(0, status->index_to_workdir->old_file.size);
	cl_assert_equal_s("modified_file", status->index_to_workdir->new_file.path);
	cl_assert(
		!git_oid_equal(&zero_id, &status->index_to_workdir->new_file.id) ||
		!(status->index_to_workdir->new_file.flags & GIT_DIFF_FLAG_VALID_ID));
	cl_assert(0 != status->index_to_workdir->new_file.mode);
	cl_assert(0 != status->index_to_workdir->new_file.size);

	git_index_free(index);
	git_status_list_free(statuslist);
}