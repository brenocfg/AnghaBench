#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 char* escape_value (char const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char const* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char*) ; 
 int git_buf_put (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int write_section(git_buf *fbuf, const char *key)
{
	int result;
	const char *dot;
	git_buf buf = GIT_BUF_INIT;

	/* All of this just for [section "subsection"] */
	dot = strchr(key, '.');
	git_buf_putc(&buf, '[');
	if (dot == NULL) {
		git_buf_puts(&buf, key);
	} else {
		char *escaped;
		git_buf_put(&buf, key, dot - key);
		escaped = escape_value(dot + 1);
		GIT_ERROR_CHECK_ALLOC(escaped);
		git_buf_printf(&buf, " \"%s\"", escaped);
		git__free(escaped);
	}
	git_buf_puts(&buf, "]\n");

	if (git_buf_oom(&buf))
		return -1;

	result = git_buf_put(fbuf, git_buf_cstr(&buf), buf.size);
	git_buf_dispose(&buf);

	return result;
}