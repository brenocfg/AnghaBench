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
struct blame_origin {int /*<<< orphan*/  num_lines; int /*<<< orphan*/  fingerprints; } ;
struct blame_line_tracker {int is_parent; int s_lno; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int* fuzzy_find_matching_lines (struct blame_origin*,struct blame_origin*,int,int,int,int) ; 
 int scan_parent_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guess_line_blames(struct blame_origin *parent,
			      struct blame_origin *target,
			      int tlno, int offset, int same, int parent_len,
			      struct blame_line_tracker *line_blames)
{
	int i, best_idx, target_idx;
	int parent_slno = tlno + offset;
	int *fuzzy_matches;

	fuzzy_matches = fuzzy_find_matching_lines(parent, target,
						  tlno, parent_slno, same,
						  parent_len);
	for (i = 0; i < same - tlno; i++) {
		target_idx = tlno + i;
		if (fuzzy_matches && fuzzy_matches[i] >= 0) {
			best_idx = fuzzy_matches[i];
		} else {
			best_idx = scan_parent_range(parent->fingerprints,
						     target->fingerprints,
						     target_idx, 0,
						     parent->num_lines);
		}
		if (best_idx >= 0) {
			line_blames[i].is_parent = 1;
			line_blames[i].s_lno = best_idx;
		} else {
			line_blames[i].is_parent = 0;
			line_blames[i].s_lno = target_idx;
		}
	}
	free(fuzzy_matches);
}