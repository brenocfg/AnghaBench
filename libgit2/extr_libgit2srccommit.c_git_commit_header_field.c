#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* raw_header; } ;
typedef  TYPE_1__ git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 scalar_t__ git__prefixcmp (char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_commit_header_field(git_buf *out, const git_commit *commit, const char *field)
{
	const char *eol, *buf = commit->raw_header;

	git_buf_clear(out);

	while ((eol = strchr(buf, '\n'))) {
		/* We can skip continuations here */
		if (buf[0] == ' ') {
			buf = eol + 1;
			continue;
		}

		/* Skip until we find the field we're after */
		if (git__prefixcmp(buf, field)) {
			buf = eol + 1;
			continue;
		}

		buf += strlen(field);
		/* Check that we're not matching a prefix but the field itself */
		if (buf[0] != ' ') {
			buf = eol + 1;
			continue;
		}

		buf++; /* skip the SP */

		git_buf_put(out, buf, eol - buf);
		if (git_buf_oom(out))
			goto oom;

		/* If the next line starts with SP, it's multi-line, we must continue */
		while (eol[1] == ' ') {
			git_buf_putc(out, '\n');
			buf = eol + 2;
			eol = strchr(buf, '\n');
			if (!eol)
				goto malformed;

			git_buf_put(out, buf, eol - buf);
		}

		if (git_buf_oom(out))
			goto oom;

		return 0;
	}

	git_error_set(GIT_ERROR_OBJECT, "no such field '%s'", field);
	return GIT_ENOTFOUND;

malformed:
	git_error_set(GIT_ERROR_OBJECT, "malformed header");
	return -1;
oom:
	git_error_set_oom();
	return -1;
}