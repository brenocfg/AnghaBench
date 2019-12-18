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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff_file_content_src ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FILE_CONTENT_SRC__BLOB (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  GIT_DIFF_FILE_CONTENT_SRC__BUF (void const*,size_t,char const*) ; 
 int patch_from_sources (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_patch_from_blob_and_buffer(
	git_patch **out,
	const git_blob *old_blob,
	const char *old_path,
	const void *buf,
	size_t buflen,
	const char *buf_path,
	const git_diff_options *opts)
{
	git_diff_file_content_src osrc =
		GIT_DIFF_FILE_CONTENT_SRC__BLOB(old_blob, old_path);
	git_diff_file_content_src nsrc =
		GIT_DIFF_FILE_CONTENT_SRC__BUF(buf, buflen, buf_path);
	return patch_from_sources(out, &osrc, &nsrc, opts);
}