#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line_len; int /*<<< orphan*/  line; } ;
struct TYPE_4__ {TYPE_3__ ctx; } ;
typedef  TYPE_1__ git_config_parser ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_parse_advance_line (TYPE_3__*) ; 
 int strip_comments (char*,int) ; 
 int unescape_line (char**,int*,char*,int) ; 

__attribute__((used)) static int parse_multiline_variable(git_config_parser *reader, git_buf *value, int in_quotes)
{
	int quote_count;
	bool multiline = true;

	while (multiline) {
		char *line = NULL, *proc_line = NULL;
		int error;

		/* Check that the next line exists */
		git_parse_advance_line(&reader->ctx);
		line = git__strndup(reader->ctx.line, reader->ctx.line_len);
		GIT_ERROR_CHECK_ALLOC(line);

		/*
		 * We've reached the end of the file, there is no continuation.
		 * (this is not an error).
		 */
		if (line[0] == '\0') {
			error = 0;
			goto out;
		}

		/* If it was just a comment, pretend it didn't exist */
		quote_count = strip_comments(line, !!in_quotes);
		if (line[0] == '\0')
			goto next;

		if ((error = unescape_line(&proc_line, &multiline,
					   line, in_quotes)) < 0)
			goto out;

		/* Add this line to the multiline var */
		if ((error = git_buf_puts(value, proc_line)) < 0)
			goto out;

next:
		git__free(line);
		git__free(proc_line);
		in_quotes = quote_count;
		continue;

out:
		git__free(line);
		git__free(proc_line);
		return error;
	}

	return 0;
}