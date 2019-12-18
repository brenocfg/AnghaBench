#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_sysdir_t ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_14__ {char const* ptr; } ;
struct TYPE_15__ {TYPE_2__ buf; int /*<<< orphan*/  (* guess ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_PATH_LIST_SEPARATOR ; 
 int /*<<< orphan*/  PATH_MAGIC ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_buf_len (TYPE_2__*) ; 
 scalar_t__ git_buf_oom (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_buf_swap (TYPE_2__*,TYPE_1__*) ; 
 TYPE_3__* git_sysdir__dirs ; 
 int /*<<< orphan*/  git_sysdir_check_selector (size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int git_sysdir_set(git_sysdir_t which, const char *search_path)
{
	const char *expand_path = NULL;
	git_buf merge = GIT_BUF_INIT;

	GIT_ERROR_CHECK_ERROR(git_sysdir_check_selector(which));

	if (search_path != NULL)
		expand_path = strstr(search_path, PATH_MAGIC);

	/* reset the default if this path has been cleared */
	if (!search_path)
		git_sysdir__dirs[which].guess(&git_sysdir__dirs[which].buf);

	/* if $PATH is not referenced, then just set the path */
	if (!expand_path) {
		if (search_path)
			git_buf_sets(&git_sysdir__dirs[which].buf, search_path);

		goto done;
	}

	/* otherwise set to join(before $PATH, old value, after $PATH) */
	if (expand_path > search_path)
		git_buf_set(&merge, search_path, expand_path - search_path);

	if (git_buf_len(&git_sysdir__dirs[which].buf))
		git_buf_join(&merge, GIT_PATH_LIST_SEPARATOR,
			merge.ptr, git_sysdir__dirs[which].buf.ptr);

	expand_path += strlen(PATH_MAGIC);
	if (*expand_path)
		git_buf_join(&merge, GIT_PATH_LIST_SEPARATOR, merge.ptr, expand_path);

	git_buf_swap(&git_sysdir__dirs[which].buf, &merge);
	git_buf_dispose(&merge);

done:
	if (git_buf_oom(&git_sysdir__dirs[which].buf))
		return -1;

	return 0;
}