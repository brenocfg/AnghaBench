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
typedef  int /*<<< orphan*/  git_blame__origin ;
struct TYPE_4__ {size_t s_lno; size_t lno; size_t num_lines; int /*<<< orphan*/ * suspect; } ;
typedef  TYPE_1__ git_blame__entry ;

/* Variables and functions */
 void* origin_incref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void split_overlap(git_blame__entry *split, git_blame__entry *e,
		size_t tlno, size_t plno, size_t same, git_blame__origin *parent)
{
	size_t chunk_end_lno;

	if (e->s_lno < tlno) {
		/* there is a pre-chunk part not blamed on the parent */
		split[0].suspect = origin_incref(e->suspect);
		split[0].lno = e->lno;
		split[0].s_lno = e->s_lno;
		split[0].num_lines = tlno - e->s_lno;
		split[1].lno = e->lno + tlno - e->s_lno;
		split[1].s_lno = plno;
	} else {
		split[1].lno = e->lno;
		split[1].s_lno = plno + (e->s_lno - tlno);
	}

	if (same < e->s_lno + e->num_lines) {
		/* there is a post-chunk part not blamed on parent */
		split[2].suspect = origin_incref(e->suspect);
		split[2].lno = e->lno + (same - e->s_lno);
		split[2].s_lno = e->s_lno + (same - e->s_lno);
		split[2].num_lines = e->s_lno + e->num_lines - same;
		chunk_end_lno = split[2].lno;
	} else {
		chunk_end_lno = e->lno + e->num_lines;
	}
	split[1].num_lines = chunk_end_lno - split[1].lno;

	/*
	 * if it turns out there is nothing to blame the parent for, forget about
	 * the splitting. !split[1].suspect signals this.
	 */
	if (split[1].num_lines < 1)
		return;
	split[1].suspect = origin_incref(parent);
}