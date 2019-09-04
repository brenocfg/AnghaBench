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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  rebase_path_author_script () ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int write_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_author_script(const char *message)
{
	struct strbuf buf = STRBUF_INIT;
	const char *eol;
	int res;

	for (;;)
		if (!*message || starts_with(message, "\n")) {
missing_author:
			/* Missing 'author' line? */
			unlink(rebase_path_author_script());
			return 0;
		} else if (skip_prefix(message, "author ", &message))
			break;
		else if ((eol = strchr(message, '\n')))
			message = eol + 1;
		else
			goto missing_author;

	strbuf_addstr(&buf, "GIT_AUTHOR_NAME='");
	while (*message && *message != '\n' && *message != '\r')
		if (skip_prefix(message, " <", &message))
			break;
		else if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\%c'", *(message++));
	strbuf_addstr(&buf, "'\nGIT_AUTHOR_EMAIL='");
	while (*message && *message != '\n' && *message != '\r')
		if (skip_prefix(message, "> ", &message))
			break;
		else if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\%c'", *(message++));
	strbuf_addstr(&buf, "'\nGIT_AUTHOR_DATE='@");
	while (*message && *message != '\n' && *message != '\r')
		if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\%c'", *(message++));
	strbuf_addch(&buf, '\'');
	res = write_message(buf.buf, buf.len, rebase_path_author_script(), 1);
	strbuf_release(&buf);
	return res;
}