#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  line_len; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {TYPE_5__ ctx; } ;
typedef  TYPE_1__ git_config_parser ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git__isspace (char const) ; 
 char* git__strndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_attach (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_parse_advance_ws (TYPE_5__*) ; 
 scalar_t__ parse_multiline_variable (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int parse_name (char**,char const**,TYPE_1__*,char*) ; 
 int strip_comments (char*,int /*<<< orphan*/ ) ; 
 int unescape_line (char**,int*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_variable(git_config_parser *reader, char **var_name, char **var_value)
{
	const char *value_start = NULL;
	char *line = NULL, *name = NULL, *value = NULL;
	int quote_count, error;
	bool multiline;

	*var_name = NULL;
	*var_value = NULL;

	git_parse_advance_ws(&reader->ctx);
	line = git__strndup(reader->ctx.line, reader->ctx.line_len);
	GIT_ERROR_CHECK_ALLOC(line);

	quote_count = strip_comments(line, 0);

	if ((error = parse_name(&name, &value_start, reader, line)) < 0)
		goto out;

	/*
	 * Now, let's try to parse the value
	 */
	if (value_start != NULL) {
		while (git__isspace(value_start[0]))
			value_start++;

		if ((error = unescape_line(&value, &multiline, value_start, 0)) < 0)
			goto out;

		if (multiline) {
			git_buf multi_value = GIT_BUF_INIT;
			git_buf_attach(&multi_value, value, 0);
			value = NULL;

			if (parse_multiline_variable(reader, &multi_value, quote_count) < 0 ||
			    git_buf_oom(&multi_value)) {
				error = -1;
				git_buf_dispose(&multi_value);
				goto out;
			}

			value = git_buf_detach(&multi_value);
		}
	}

	*var_name = name;
	*var_value = value;
	name = NULL;
	value = NULL;

out:
	git__free(name);
	git__free(value);
	git__free(line);
	return error;
}