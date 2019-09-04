#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_sysdir_t ;
struct TYPE_4__ {size_t size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/  git_buf_copy_cstr (char*,size_t,TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_sysdir_check_selector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sysdir_get (TYPE_1__ const**,int /*<<< orphan*/ ) ; 

int git_sysdir_get_str(
	char *out,
	size_t outlen,
	git_sysdir_t which)
{
	const git_buf *path = NULL;

	GIT_ERROR_CHECK_ERROR(git_sysdir_check_selector(which));
	GIT_ERROR_CHECK_ERROR(git_sysdir_get(&path, which));

	if (!out || path->size >= outlen) {
		git_error_set(GIT_ERROR_NOMEMORY, "buffer is too short for the path");
		return GIT_EBUFS;
	}

	git_buf_copy_cstr(out, outlen, path);
	return 0;
}