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
struct TYPE_11__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,unsigned char) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  git_buf_swap (TYPE_1__*,TYPE_1__*) ; 

int git_buf_quote(git_buf *buf)
{
	const char whitespace[] = { 'a', 'b', 't', 'n', 'v', 'f', 'r' };
	git_buf quoted = GIT_BUF_INIT;
	size_t i = 0;
	bool quote = false;
	int error = 0;

	/* walk to the first char that needs quoting */
	if (buf->size && buf->ptr[0] == '!')
		quote = true;

	for (i = 0; !quote && i < buf->size; i++) {
		if (buf->ptr[i] == '"' || buf->ptr[i] == '\\' ||
			buf->ptr[i] < ' ' || buf->ptr[i] > '~') {
			quote = true;
			break;
		}
	}

	if (!quote)
		goto done;

	git_buf_putc(&quoted, '"');
	git_buf_put(&quoted, buf->ptr, i);

	for (; i < buf->size; i++) {
		/* whitespace - use the map above, which is ordered by ascii value */
		if (buf->ptr[i] >= '\a' && buf->ptr[i] <= '\r') {
			git_buf_putc(&quoted, '\\');
			git_buf_putc(&quoted, whitespace[buf->ptr[i] - '\a']);
		}

		/* double quote and backslash must be escaped */
		else if (buf->ptr[i] == '"' || buf->ptr[i] == '\\') {
			git_buf_putc(&quoted, '\\');
			git_buf_putc(&quoted, buf->ptr[i]);
		}

		/* escape anything unprintable as octal */
		else if (buf->ptr[i] != ' ' &&
				(buf->ptr[i] < '!' || buf->ptr[i] > '~')) {
			git_buf_printf(&quoted, "\\%03o", (unsigned char)buf->ptr[i]);
		}

		/* yay, printable! */
		else {
			git_buf_putc(&quoted, buf->ptr[i]);
		}
	}

	git_buf_putc(&quoted, '"');

	if (git_buf_oom(&quoted)) {
		error = -1;
		goto done;
	}

	git_buf_swap(&quoted, buf);

done:
	git_buf_dispose(&quoted);
	return error;
}