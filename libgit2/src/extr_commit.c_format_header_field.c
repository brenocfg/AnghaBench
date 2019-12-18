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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void format_header_field(git_buf *out, const char *field, const char *content)
{
	const char *lf;

	assert(out && field && content);

	git_buf_puts(out, field);
	git_buf_putc(out, ' ');

	while ((lf = strchr(content, '\n')) != NULL) {
		git_buf_put(out, content, lf - content);
		git_buf_puts(out, "\n ");
		content = lf + 1;
	}

	git_buf_puts(out, content);
	git_buf_putc(out, '\n');
}