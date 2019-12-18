#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct patch_id_args {int /*<<< orphan*/  ctx; scalar_t__ first_file; int /*<<< orphan*/  result; } ;
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
struct TYPE_12__ {TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 TYPE_4__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_UNUSED (float) ; 
 int flush_hunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int git_buf_printf (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_spaces (TYPE_4__*) ; 

__attribute__((used)) static int file_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload)
{
	struct patch_id_args *args = (struct patch_id_args *) payload;
	git_buf buf = GIT_BUF_INIT;
	int error;

	GIT_UNUSED(progress);

	if (!args->first_file &&
	    (error = flush_hunk(&args->result, &args->ctx)) < 0)
		goto out;
	args->first_file = 0;

	if ((error = git_buf_printf(&buf,
				    "diff--gita/%sb/%s---a/%s+++b/%s",
				    delta->old_file.path,
				    delta->new_file.path,
				    delta->old_file.path,
				    delta->new_file.path)) < 0)
		goto out;

	strip_spaces(&buf);

	if ((error = git_hash_update(&args->ctx, buf.ptr, buf.size)) < 0)
		goto out;

out:
	git_buf_dispose(&buf);
	return error;
}