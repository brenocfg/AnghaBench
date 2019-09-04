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
typedef  int /*<<< orphan*/  xdfile_t ;
struct xdlgroup {long end; long start; } ;
struct split_score {int /*<<< orphan*/  penalty; int /*<<< orphan*/  effective_indent; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct split_measurement {int dummy; } ;

/* Variables and functions */
 long XDF_INDENT_HEURISTIC ; 
 int /*<<< orphan*/  group_init (int /*<<< orphan*/ *,struct xdlgroup*) ; 
 scalar_t__ group_next (int /*<<< orphan*/ *,struct xdlgroup*) ; 
 scalar_t__ group_previous (int /*<<< orphan*/ *,struct xdlgroup*) ; 
 scalar_t__ group_slide_down (int /*<<< orphan*/ *,struct xdlgroup*,long) ; 
 scalar_t__ group_slide_up (int /*<<< orphan*/ *,struct xdlgroup*,long) ; 
 int /*<<< orphan*/  measure_split (int /*<<< orphan*/ *,long,struct split_measurement*) ; 
 int /*<<< orphan*/  score_add_split (struct split_measurement*,struct split_score*) ; 
 scalar_t__ score_cmp (struct split_score*,struct split_score*) ; 
 int /*<<< orphan*/  xdl_bug (char*) ; 

int xdl_change_compact(xdfile_t *xdf, xdfile_t *xdfo, long flags) {
	struct xdlgroup g, go;
	long earliest_end, end_matching_other;
	long groupsize;

	group_init(xdf, &g);
	group_init(xdfo, &go);

	while (1) {
		/* If the group is empty in the to-be-compacted file, skip it: */
		if (g.end == g.start)
			goto next;

		/*
		 * Now shift the change up and then down as far as possible in
		 * each direction. If it bumps into any other changes, merge them.
		 */
		do {
			groupsize = g.end - g.start;

			/*
			 * Keep track of the last "end" index that causes this
			 * group to align with a group of changed lines in the
			 * other file. -1 indicates that we haven't found such
			 * a match yet:
			 */
			end_matching_other = -1;

			/* Shift the group backward as much as possible: */
			while (!group_slide_up(xdf, &g, flags))
				if (group_previous(xdfo, &go))
					xdl_bug("group sync broken sliding up");

			/*
			 * This is this highest that this group can be shifted.
			 * Record its end index:
			 */
			earliest_end = g.end;

			if (go.end > go.start)
				end_matching_other = g.end;

			/* Now shift the group forward as far as possible: */
			while (1) {
				if (group_slide_down(xdf, &g, flags))
					break;
				if (group_next(xdfo, &go))
					xdl_bug("group sync broken sliding down");

				if (go.end > go.start)
					end_matching_other = g.end;
			}
		} while (groupsize != g.end - g.start);

		/*
		 * If the group can be shifted, then we can possibly use this
		 * freedom to produce a more intuitive diff.
		 *
		 * The group is currently shifted as far down as possible, so the
		 * heuristics below only have to handle upwards shifts.
		 */

		if (g.end == earliest_end) {
			/* no shifting was possible */
		} else if (end_matching_other != -1) {
			/*
			 * Move the possibly merged group of changes back to line
			 * up with the last group of changes from the other file
			 * that it can align with.
			 */
			while (go.end == go.start) {
				if (group_slide_up(xdf, &g, flags))
					xdl_bug("match disappeared");
				if (group_previous(xdfo, &go))
					xdl_bug("group sync broken sliding to match");
			}
		} else if (flags & XDF_INDENT_HEURISTIC) {
			/*
			 * Indent heuristic: a group of pure add/delete lines
			 * implies two splits, one between the end of the "before"
			 * context and the start of the group, and another between
			 * the end of the group and the beginning of the "after"
			 * context. Some splits are aesthetically better and some
			 * are worse. We compute a badness "score" for each split,
			 * and add the scores for the two splits to define a
			 * "score" for each position that the group can be shifted
			 * to. Then we pick the shift with the lowest score.
			 */
			long shift, best_shift = -1;
			struct split_score best_score;

			for (shift = earliest_end; shift <= g.end; shift++) {
				struct split_measurement m;
				struct split_score score = {0, 0};

				measure_split(xdf, shift, &m);
				score_add_split(&m, &score);
				measure_split(xdf, shift - groupsize, &m);
				score_add_split(&m, &score);
				if (best_shift == -1 ||
				    score_cmp(&score, &best_score) <= 0) {
					best_score.effective_indent = score.effective_indent;
					best_score.penalty = score.penalty;
					best_shift = shift;
				}
			}

			while (g.end > best_shift) {
				if (group_slide_up(xdf, &g, flags))
					xdl_bug("best shift unreached");
				if (group_previous(xdfo, &go))
					xdl_bug("group sync broken sliding to blank line");
			}
		}

	next:
		/* Move past the just-processed group: */
		if (group_next(xdf, &g))
			break;
		if (group_next(xdfo, &go))
			xdl_bug("group sync broken moving to next group");
	}

	if (!group_next(xdfo, &go))
		xdl_bug("group sync broken at end of file");

	return 0;
}