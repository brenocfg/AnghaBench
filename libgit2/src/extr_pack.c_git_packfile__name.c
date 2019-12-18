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
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

int git_packfile__name(char **out, const char *path)
{
	size_t path_len;
	git_buf buf = GIT_BUF_INIT;

	path_len = strlen(path);

	if (path_len < strlen(".idx"))
		return git_odb__error_notfound("invalid packfile path", NULL, 0);

	if (git_buf_printf(&buf, "%.*s.pack", (int)(path_len - strlen(".idx")), path) < 0)
		return -1;

	*out = git_buf_detach(&buf);
	return 0;
}