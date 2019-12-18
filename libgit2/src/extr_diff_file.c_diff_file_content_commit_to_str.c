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
typedef  int /*<<< orphan*/  oid ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; TYPE_2__ map; TYPE_1__* file; int /*<<< orphan*/  repo; } ;
typedef  TYPE_3__ git_diff_file_content ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_DIFF_FLAG_VALID_ID ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__FREE_DATA ; 
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNSPECIFIED ; 
 scalar_t__ GIT_SUBMODULE_STATUS_IS_WD_DIRTY (unsigned int) ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char*,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_submodule_head_id (int /*<<< orphan*/ *) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_submodule_status (unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_submodule_wd_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_file_content_commit_to_str(
	git_diff_file_content *fc, bool check_status)
{
	char oid[GIT_OID_HEXSZ+1];
	git_buf content = GIT_BUF_INIT;
	const char *status = "";

	if (check_status) {
		int error = 0;
		git_submodule *sm = NULL;
		unsigned int sm_status = 0;
		const git_oid *sm_head;

		if ((error = git_submodule_lookup(&sm, fc->repo, fc->file->path)) < 0) {
			/* GIT_EEXISTS means a "submodule" that has not been git added */
			if (error == GIT_EEXISTS) {
				git_error_clear();
				error = 0;
			}
			return error;
		}

		if ((error = git_submodule_status(&sm_status, fc->repo, fc->file->path, GIT_SUBMODULE_IGNORE_UNSPECIFIED)) < 0) {
			git_submodule_free(sm);
			return error;
		}

		/* update OID if we didn't have it previously */
		if ((fc->file->flags & GIT_DIFF_FLAG_VALID_ID) == 0 &&
			((sm_head = git_submodule_wd_id(sm)) != NULL ||
			 (sm_head = git_submodule_head_id(sm)) != NULL))
		{
			git_oid_cpy(&fc->file->id, sm_head);
			fc->file->flags |= GIT_DIFF_FLAG_VALID_ID;
		}

		if (GIT_SUBMODULE_STATUS_IS_WD_DIRTY(sm_status))
			status = "-dirty";

		git_submodule_free(sm);
	}

	git_oid_tostr(oid, sizeof(oid), &fc->file->id);
	if (git_buf_printf(&content, "Subproject commit %s%s\n", oid, status) < 0)
		return -1;

	fc->map.len  = git_buf_len(&content);
	fc->map.data = git_buf_detach(&content);
	fc->flags |= GIT_DIFF_FLAG__FREE_DATA;

	return 0;
}