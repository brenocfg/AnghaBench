#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int new_lineno; int old_lineno; } ;
typedef  TYPE_1__ git_xdiff_info ;
struct TYPE_6__ {char const* content; size_t content_len; int origin; int old_lineno; int new_lineno; scalar_t__ num_lines; } ;
typedef  TYPE_2__ git_diff_line ;

/* Variables and functions */
#define  GIT_DIFF_LINE_ADDITION 133 
#define  GIT_DIFF_LINE_ADD_EOFNL 132 
#define  GIT_DIFF_LINE_CONTEXT 131 
#define  GIT_DIFF_LINE_CONTEXT_EOFNL 130 
#define  GIT_DIFF_LINE_DELETION 129 
#define  GIT_DIFF_LINE_DEL_EOFNL 128 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int diff_update_lines(
	git_xdiff_info *info,
	git_diff_line *line,
	const char *content,
	size_t content_len)
{
	const char *scan = content, *scan_end = content + content_len;

	for (line->num_lines = 0; scan < scan_end; ++scan)
		if (*scan == '\n')
			++line->num_lines;

	line->content     = content;
	line->content_len = content_len;

	/* expect " "/"-"/"+", then data */
	switch (line->origin) {
	case GIT_DIFF_LINE_ADDITION:
	case GIT_DIFF_LINE_DEL_EOFNL:
		line->old_lineno = -1;
		line->new_lineno = info->new_lineno;
		info->new_lineno += (int)line->num_lines;
		break;
	case GIT_DIFF_LINE_DELETION:
	case GIT_DIFF_LINE_ADD_EOFNL:
		line->old_lineno = info->old_lineno;
		line->new_lineno = -1;
		info->old_lineno += (int)line->num_lines;
		break;
	case GIT_DIFF_LINE_CONTEXT:
	case GIT_DIFF_LINE_CONTEXT_EOFNL:
		line->old_lineno = info->old_lineno;
		line->new_lineno = info->new_lineno;
		info->old_lineno += (int)line->num_lines;
		info->new_lineno += (int)line->num_lines;
		break;
	default:
		git_error_set(GIT_ERROR_INVALID, "unknown diff line origin %02x",
			(unsigned int)line->origin);
		return -1;
	}

	return 0;
}