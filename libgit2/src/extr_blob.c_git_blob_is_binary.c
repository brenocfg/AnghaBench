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
typedef  int /*<<< orphan*/  git_off_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILTER_BYTES_TO_CHECK_NUL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_blob_rawsize (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int git_buf_text_is_binary (int /*<<< orphan*/ *) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_blob_is_binary(const git_blob *blob)
{
	git_buf content = GIT_BUF_INIT;
	git_off_t size;

	assert(blob);

	size = git_blob_rawsize(blob);

	git_buf_attach_notowned(&content, git_blob_rawcontent(blob),
		(size_t)min(size, GIT_FILTER_BYTES_TO_CHECK_NUL));
	return git_buf_text_is_binary(&content);
}