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
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_diff_hunk_cb ;
typedef  int /*<<< orphan*/  git_diff_file_content_src ;
typedef  int /*<<< orphan*/  git_diff_file_cb ;
typedef  int /*<<< orphan*/  git_diff_binary_cb ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FILE_CONTENT_SRC__BLOB (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  GIT_DIFF_FILE_CONTENT_SRC__BUF (char const*,size_t,char const*) ; 
 int diff_from_sources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int git_diff_blob_to_buffer(
	const git_blob *old_blob,
	const char *old_path,
	const char *buf,
	size_t buflen,
	const char *buf_path,
	const git_diff_options *opts,
	git_diff_file_cb file_cb,
	git_diff_binary_cb binary_cb,
	git_diff_hunk_cb hunk_cb,
	git_diff_line_cb data_cb,
	void *payload)
{
	git_diff_file_content_src osrc =
		GIT_DIFF_FILE_CONTENT_SRC__BLOB(old_blob, old_path);
	git_diff_file_content_src nsrc =
		GIT_DIFF_FILE_CONTENT_SRC__BUF(buf, buflen, buf_path);
	return diff_from_sources(
		&osrc, &nsrc, opts, file_cb, binary_cb, hunk_cb, data_cb, payload);
}