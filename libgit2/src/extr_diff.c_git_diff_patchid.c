#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct patch_id_args {int first_file; int /*<<< orphan*/  ctx; int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_diff_patchid_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_PATCHID_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  file_cb ; 
 int flush_hunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct patch_id_args*) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct patch_id_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patchid_line_cb ; 

int git_diff_patchid(git_oid *out, git_diff *diff, git_diff_patchid_options *opts)
{
	struct patch_id_args args;
	int error;

	GIT_ERROR_CHECK_VERSION(
		opts, GIT_DIFF_PATCHID_OPTIONS_VERSION, "git_diff_patchid_options");

	memset(&args, 0, sizeof(args));
	args.first_file = 1;
	if ((error = git_hash_ctx_init(&args.ctx)) < 0)
		goto out;

	if ((error = git_diff_foreach(diff, file_cb, NULL, NULL, patchid_line_cb, &args)) < 0)
		goto out;

	if ((error = (flush_hunk(&args.result, &args.ctx))) < 0)
		goto out;

	git_oid_cpy(out, &args.result);

out:
	git_hash_ctx_cleanup(&args.ctx);
	return error;
}