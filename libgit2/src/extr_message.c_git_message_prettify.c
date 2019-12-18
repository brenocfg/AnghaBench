#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_sanitize (TYPE_1__*) ; 
 size_t line_length_without_trailing_spaces (char const*,size_t) ; 
 char* memchr (char const*,char,size_t const) ; 
 size_t strlen (char const*) ; 

int git_message_prettify(git_buf *message_out, const char *message, int strip_comments, char comment_char)
{
	const size_t message_len = strlen(message);

	int consecutive_empty_lines = 0;
	size_t i, line_length, rtrimmed_line_length;
	char *next_newline;

	git_buf_sanitize(message_out);

	for (i = 0; i < strlen(message); i += line_length) {
		next_newline = memchr(message + i, '\n', message_len - i);

		if (next_newline != NULL) {
			line_length = next_newline - (message + i) + 1;
		} else {
			line_length = message_len - i;
		}

		if (strip_comments && line_length && message[i] == comment_char)
			continue;

		rtrimmed_line_length = line_length_without_trailing_spaces(message + i, line_length);

		if (!rtrimmed_line_length) {
			consecutive_empty_lines++;
			continue;
		}

		if (consecutive_empty_lines > 0 && message_out->size > 0)
			git_buf_putc(message_out, '\n');

		consecutive_empty_lines = 0;
		git_buf_put(message_out, message + i, rtrimmed_line_length);
		git_buf_putc(message_out, '\n');
	}

	return git_buf_oom(message_out) ? -1 : 0;
}