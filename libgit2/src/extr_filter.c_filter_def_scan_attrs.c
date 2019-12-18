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
 scalar_t__ git__isspace (char const) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static int filter_def_scan_attrs(
	git_buf *attrs, size_t *nattr, size_t *nmatch, const char *attr_str)
{
	const char *start, *scan = attr_str;
	int has_eq;

	*nattr = *nmatch = 0;

	if (!scan)
		return 0;

	while (*scan) {
		while (git__isspace(*scan)) scan++;

		for (start = scan, has_eq = 0; *scan && !git__isspace(*scan); ++scan) {
			if (*scan == '=')
				has_eq = 1;
		}

		if (scan > start) {
			(*nattr)++;
			if (has_eq || *start == '-' || *start == '+' || *start == '!')
				(*nmatch)++;

			if (has_eq)
				git_buf_putc(attrs, '=');
			git_buf_put(attrs, start, scan - start);
			git_buf_putc(attrs, '\0');
		}
	}

	return 0;
}