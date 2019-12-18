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
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ git__isalpha (char const) ; 
 scalar_t__ git__isdigit (char const) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int canonicalize_url(git_buf *out, const char *in)
{
	if (in == NULL || strlen(in) == 0) {
		git_error_set(GIT_ERROR_INVALID, "cannot set empty URL");
		return GIT_EINVALIDSPEC;
	}

#ifdef GIT_WIN32
	/* Given a UNC path like \\server\path, we need to convert this
	 * to //server/path for compatibility with core git.
	 */
	if (in[0] == '\\' && in[1] == '\\' &&
		(git__isalpha(in[2]) || git__isdigit(in[2]))) {
		const char *c;
		for (c = in; *c; c++)
			git_buf_putc(out, *c == '\\' ? '/' : *c);

		return git_buf_oom(out) ? -1 : 0;
	}
#endif

	return git_buf_puts(out, in);
}