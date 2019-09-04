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
 int /*<<< orphan*/  GIT_ERROR_CHECK_BLOBSIZE (scalar_t__) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int git_buf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int git_blob__getbuf(git_buf *buffer, git_blob *blob)
{
	git_off_t size = git_blob_rawsize(blob);

	GIT_ERROR_CHECK_BLOBSIZE(size);
	return git_buf_set(buffer, git_blob_rawcontent(blob), (size_t)size);
}