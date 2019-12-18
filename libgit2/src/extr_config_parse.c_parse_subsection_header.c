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
typedef  int /*<<< orphan*/  git_config_parser ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int INT_MAX ; 
 scalar_t__ git__isspace (char const) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_grow (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  set_parse_error (int /*<<< orphan*/ *,int,char*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int parse_subsection_header(git_config_parser *reader, const char *line, size_t pos, const char *base_name, char **section_name)
{
	int c, rpos;
	const char *first_quote, *last_quote;
	const char *line_start = line;
	git_buf buf = GIT_BUF_INIT;
	size_t quoted_len, alloc_len, base_name_len = strlen(base_name);

	/* Skip any additional whitespace before our section name */
	while (git__isspace(line[pos]))
		pos++;

	/* We should be at the first quotation mark. */
	if (line[pos] != '"') {
		set_parse_error(reader, 0, "missing quotation marks in section header");
		goto end_error;
	}

	first_quote = &line[pos];
	last_quote = strrchr(line, '"');
	quoted_len = last_quote - first_quote;

	if ((last_quote - line) > INT_MAX) {
		set_parse_error(reader, 0, "invalid section header, line too long");
		goto end_error;
	}

	if (quoted_len == 0) {
		set_parse_error(reader, 0, "missing closing quotation mark in section header");
		goto end_error;
	}

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, base_name_len, quoted_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 2);

	if (git_buf_grow(&buf, alloc_len) < 0 ||
	    git_buf_printf(&buf, "%s.", base_name) < 0)
		goto end_error;

	rpos = 0;

	line = first_quote;
	c = line[++rpos];

	/*
	 * At the end of each iteration, whatever is stored in c will be
	 * added to the string. In case of error, jump to out
	 */
	do {

		switch (c) {
		case 0:
			set_parse_error(reader, 0, "unexpected end-of-line in section header");
			goto end_error;

		case '"':
			goto end_parse;

		case '\\':
			c = line[++rpos];

			if (c == 0) {
				set_parse_error(reader, rpos, "unexpected end-of-line in section header");
				goto end_error;
			}

		default:
			break;
		}

		git_buf_putc(&buf, (char)c);
		c = line[++rpos];
	} while (line + rpos < last_quote);

end_parse:
	if (git_buf_oom(&buf))
		goto end_error;

	if (line[rpos] != '"' || line[rpos + 1] != ']') {
		set_parse_error(reader, rpos, "unexpected text after closing quotes");
		git_buf_dispose(&buf);
		return -1;
	}

	*section_name = git_buf_detach(&buf);
	return (int)(&line[rpos + 2] - line_start); /* rpos is at the closing quote */

end_error:
	git_buf_dispose(&buf);

	return -1;
}