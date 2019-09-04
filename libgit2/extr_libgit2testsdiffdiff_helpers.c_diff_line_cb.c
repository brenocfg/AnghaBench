#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int origin; } ;
typedef  TYPE_1__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;
struct TYPE_5__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
#define  GIT_DIFF_LINE_ADDITION 133 
#define  GIT_DIFF_LINE_ADD_EOFNL 132 
#define  GIT_DIFF_LINE_CONTEXT 131 
#define  GIT_DIFF_LINE_CONTEXT_EOFNL 130 
#define  GIT_DIFF_LINE_DELETION 129 
#define  GIT_DIFF_LINE_DEL_EOFNL 128 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 

int diff_line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload)
{
	diff_expects *e = payload;

	GIT_UNUSED(delta);
	GIT_UNUSED(hunk);

	e->lines++;
	switch (line->origin) {
	case GIT_DIFF_LINE_CONTEXT:
	case GIT_DIFF_LINE_CONTEXT_EOFNL: /* techically not a line */
		e->line_ctxt++;
		break;
	case GIT_DIFF_LINE_ADDITION:
	case GIT_DIFF_LINE_ADD_EOFNL: /* technically not a line add */
		e->line_adds++;
		break;
	case GIT_DIFF_LINE_DELETION:
	case GIT_DIFF_LINE_DEL_EOFNL: /* technically not a line delete */
		e->line_dels++;
		break;
	default:
		break;
	}
	return 0;
}