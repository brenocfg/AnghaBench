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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int extract_curly_braces_content(git_buf *buf, const char *spec, size_t *pos)
{
	git_buf_clear(buf);

	assert(spec[*pos] == '^' || spec[*pos] == '@');

	(*pos)++;

	if (spec[*pos] == '\0' || spec[*pos] != '{')
		return GIT_EINVALIDSPEC;

	(*pos)++;

	while (spec[*pos] != '}') {
		if (spec[*pos] == '\0')
			return GIT_EINVALIDSPEC;

		git_buf_putc(buf, spec[(*pos)++]);
	}

	(*pos)++;

	return 0;
}