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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EBUFS ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  git_buf_copy_cstr (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 size_t git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_reference__normalize_name (int /*<<< orphan*/ *,char const*,unsigned int) ; 

int git_reference_normalize_name(
	char *buffer_out,
	size_t buffer_size,
	const char *name,
	unsigned int flags)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if ((error = git_reference__normalize_name(&buf, name, flags)) < 0)
		goto cleanup;

	if (git_buf_len(&buf) > buffer_size - 1) {
		git_error_set(
		GIT_ERROR_REFERENCE,
		"the provided buffer is too short to hold the normalization of '%s'", name);
		error = GIT_EBUFS;
		goto cleanup;
	}

	git_buf_copy_cstr(buffer_out, buffer_size, &buf);

	error = 0;

cleanup:
	git_buf_dispose(&buf);
	return error;
}