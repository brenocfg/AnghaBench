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
typedef  int /*<<< orphan*/  git_parse_ctx ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ advance_until (char const**,size_t*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_rtrim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_parse_advance_ws (int /*<<< orphan*/ *) ; 
 scalar_t__ is_eol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_mailmap_entry(
	git_buf *real_name, git_buf *real_email,
	git_buf *replace_name, git_buf *replace_email,
	git_parse_ctx *ctx)
{
	const char *start;
	size_t len;

	git_buf_clear(real_name);
	git_buf_clear(real_email);
	git_buf_clear(replace_name);
	git_buf_clear(replace_email);

	git_parse_advance_ws(ctx);
	if (is_eol(ctx))
		return -1; /* blank line */

	/* Parse the real name */
	if (advance_until(&start, &len, ctx, '<') < 0)
		return -1;

	git_buf_attach_notowned(real_name, start, len);
	git_buf_rtrim(real_name);

	/*
	 * If this is the last email in the line, this is the email to replace,
	 * otherwise, it's the real email.
	 */
	if (advance_until(&start, &len, ctx, '>') < 0)
		return -1;

	/* If we aren't at the end of the line, parse a second name and email */
	if (!is_eol(ctx)) {
		git_buf_attach_notowned(real_email, start, len);

		git_parse_advance_ws(ctx);
		if (advance_until(&start, &len, ctx, '<') < 0)
			return -1;
		git_buf_attach_notowned(replace_name, start, len);
		git_buf_rtrim(replace_name);

		if (advance_until(&start, &len, ctx, '>') < 0)
			return -1;
	}

	git_buf_attach_notowned(replace_email, start, len);

	if (!is_eol(ctx))
		return -1;

	return 0;
}