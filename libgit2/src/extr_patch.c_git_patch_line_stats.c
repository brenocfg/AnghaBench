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
typedef  int /*<<< orphan*/  totals ;
struct TYPE_5__ {int /*<<< orphan*/  lines; } ;
typedef  TYPE_1__ git_patch ;
struct TYPE_6__ {int origin; } ;
typedef  TYPE_2__ git_diff_line ;

/* Variables and functions */
#define  GIT_DIFF_LINE_ADDITION 130 
#define  GIT_DIFF_LINE_CONTEXT 129 
#define  GIT_DIFF_LINE_DELETION 128 
 TYPE_2__* git_array_get (int /*<<< orphan*/ ,size_t) ; 
 size_t git_array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

int git_patch_line_stats(
	size_t *total_ctxt,
	size_t *total_adds,
	size_t *total_dels,
	const git_patch *patch)
{
	size_t totals[3], idx;

	memset(totals, 0, sizeof(totals));

	for (idx = 0; idx < git_array_size(patch->lines); ++idx) {
		git_diff_line *line = git_array_get(patch->lines, idx);
		if (!line)
			continue;

		switch (line->origin) {
		case GIT_DIFF_LINE_CONTEXT:  totals[0]++; break;
		case GIT_DIFF_LINE_ADDITION: totals[1]++; break;
		case GIT_DIFF_LINE_DELETION: totals[2]++; break;
		default:
			/* diff --stat and --numstat don't count EOFNL marks because
			* they will always be paired with a ADDITION or DELETION line.
			*/
			break;
		}
	}

	if (total_ctxt)
		*total_ctxt = totals[0];
	if (total_adds)
		*total_adds = totals[1];
	if (total_dels)
		*total_dels = totals[2];

	return 0;
}