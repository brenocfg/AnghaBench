#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int INT_MAX ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 size_t git_buf_len (TYPE_1__*) ; 
 int git_buf_printf (TYPE_1__*,char*,int) ; 
 int git_buf_putc (TYPE_1__*,char) ; 
 int git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_path_suffixed(git_buf *path, const char *suffix)
{
	size_t path_len;
	int i = 0, error = 0;

	if ((error = git_buf_putc(path, '~')) < 0 || (error = git_buf_puts(path, suffix)) < 0)
		return -1;

	path_len = git_buf_len(path);

	while (git_path_exists(git_buf_cstr(path)) && i < INT_MAX) {
		git_buf_truncate(path, path_len);

		if ((error = git_buf_putc(path, '_')) < 0 ||
			(error = git_buf_printf(path, "%d", i)) < 0)
			return error;

		i++;
	}

	if (i == INT_MAX) {
		git_buf_truncate(path, path_len);

		git_error_set(GIT_ERROR_CHECKOUT, "could not write '%s': working directory file exists", path->ptr);
		return GIT_EEXISTS;
	}

	return 0;
}