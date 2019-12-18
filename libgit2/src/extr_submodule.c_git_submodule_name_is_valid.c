#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_PATH_REJECT_FILESYSTEM_DEFAULTS ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_path_isvalid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int git_path_normalize_slashes (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_submodule_name_is_valid(git_repository *repo, const char *name, int flags)
{
	git_buf buf = GIT_BUF_INIT;
	int error, isvalid;

	if (flags == 0)
		flags = GIT_PATH_REJECT_FILESYSTEM_DEFAULTS;

	/* Avoid allocating a new string if we can avoid it */
	if (strchr(name, '\\') != NULL) {
		if ((error = git_path_normalize_slashes(&buf, name)) < 0)
			return error;
	} else {
		git_buf_attach_notowned(&buf, name, strlen(name));
	}

	isvalid =  git_path_isvalid(repo, buf.ptr, 0, flags);
	git_buf_dispose(&buf);

	return isvalid;
}