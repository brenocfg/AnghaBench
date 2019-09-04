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
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int buf_from_blob(git_buf *out, git_blob *blob)
{
	git_off_t rawsize = git_blob_rawsize(blob);

	if (!git__is_sizet(rawsize)) {
		git_error_set(GIT_ERROR_OS, "blob is too large to filter");
		return -1;
	}

	git_buf_attach_notowned(out, git_blob_rawcontent(blob), (size_t)rawsize);
	return 0;
}