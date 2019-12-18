#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int origin; } ;
typedef  TYPE_1__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;

/* Variables and functions */
#define  GIT_DIFF_LINE_ADDITION 133 
#define  GIT_DIFF_LINE_ADD_EOFNL 132 
#define  GIT_DIFF_LINE_DELETION 131 
#define  GIT_DIFF_LINE_DEL_EOFNL 130 
#define  GIT_DIFF_LINE_FILE_HDR 129 
#define  GIT_DIFF_LINE_HUNK_HDR 128 
 int /*<<< orphan*/ * colors ; 
 int diff_output (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int color_printer(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *data)
{
	int *last_color = data, color = 0;

	(void)delta; (void)hunk;

	if (*last_color >= 0) {
		switch (line->origin) {
		case GIT_DIFF_LINE_ADDITION:  color = 3; break;
		case GIT_DIFF_LINE_DELETION:  color = 2; break;
		case GIT_DIFF_LINE_ADD_EOFNL: color = 3; break;
		case GIT_DIFF_LINE_DEL_EOFNL: color = 2; break;
		case GIT_DIFF_LINE_FILE_HDR:  color = 1; break;
		case GIT_DIFF_LINE_HUNK_HDR:  color = 4; break;
		default: break;
		}

		if (color != *last_color) {
			if (*last_color == 1 || color == 1)
				fputs(colors[0], stdout);
			fputs(colors[color], stdout);
			*last_color = color;
		}
	}

	return diff_output(delta, hunk, line, stdout);
}