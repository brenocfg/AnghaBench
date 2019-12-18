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
struct format_commit_context {int padding; int flush_type; int /*<<< orphan*/  truncate; } ;
typedef  enum flush_type { ____Placeholder_flush_type } flush_type ;

/* Variables and functions */
 int flush_both ; 
 int flush_left ; 
 int flush_left_and_steal ; 
 int flush_right ; 
 scalar_t__ starts_with (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 int strcspn (char const*,char*) ; 
 int strtol (char const*,char**,int) ; 
 scalar_t__ term_columns () ; 
 int /*<<< orphan*/  trunc_left ; 
 int /*<<< orphan*/  trunc_middle ; 
 int /*<<< orphan*/  trunc_none ; 
 int /*<<< orphan*/  trunc_right ; 

__attribute__((used)) static size_t parse_padding_placeholder(const char *placeholder,
					struct format_commit_context *c)
{
	const char *ch = placeholder;
	enum flush_type flush_type;
	int to_column = 0;

	switch (*ch++) {
	case '<':
		flush_type = flush_right;
		break;
	case '>':
		if (*ch == '<') {
			flush_type = flush_both;
			ch++;
		} else if (*ch == '>') {
			flush_type = flush_left_and_steal;
			ch++;
		} else
			flush_type = flush_left;
		break;
	default:
		return 0;
	}

	/* the next value means "wide enough to that column" */
	if (*ch == '|') {
		to_column = 1;
		ch++;
	}

	if (*ch == '(') {
		const char *start = ch + 1;
		const char *end = start + strcspn(start, ",)");
		char *next;
		int width;
		if (!end || end == start)
			return 0;
		width = strtol(start, &next, 10);
		if (next == start || width == 0)
			return 0;
		if (width < 0) {
			if (to_column)
				width += term_columns();
			if (width < 0)
				return 0;
		}
		c->padding = to_column ? -width : width;
		c->flush_type = flush_type;

		if (*end == ',') {
			start = end + 1;
			end = strchr(start, ')');
			if (!end || end == start)
				return 0;
			if (starts_with(start, "trunc)"))
				c->truncate = trunc_right;
			else if (starts_with(start, "ltrunc)"))
				c->truncate = trunc_left;
			else if (starts_with(start, "mtrunc)"))
				c->truncate = trunc_middle;
			else
				return 0;
		} else
			c->truncate = trunc_none;

		return end - placeholder + 1;
	}
	return 0;
}