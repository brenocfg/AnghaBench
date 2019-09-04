#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct combine_diff_state {long ob; long on; long nb; long nn; long lno; size_t n; TYPE_1__* sline; int /*<<< orphan*/  num_parent; TYPE_1__* lost_bucket; } ;
struct TYPE_2__ {long* p_lno; } ;

/* Variables and functions */
 long* xcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void consume_hunk(void *state_,
			 long ob, long on,
			 long nb, long nn,
			 const char *funcline, long funclen)
{
	struct combine_diff_state *state = state_;

	state->ob = ob;
	state->on = on;
	state->nb = nb;
	state->nn = nn;
	state->lno = state->nb;
	if (state->nn == 0) {
		/* @@ -X,Y +N,0 @@ removed Y lines
		 * that would have come *after* line N
		 * in the result.  Our lost buckets hang
		 * to the line after the removed lines,
		 *
		 * Note that this is correct even when N == 0,
		 * in which case the hunk removes the first
		 * line in the file.
		 */
		state->lost_bucket = &state->sline[state->nb];
		if (!state->nb)
			state->nb = 1;
	} else {
		state->lost_bucket = &state->sline[state->nb-1];
	}
	if (!state->sline[state->nb-1].p_lno)
		state->sline[state->nb-1].p_lno =
			xcalloc(state->num_parent, sizeof(unsigned long));
	state->sline[state->nb-1].p_lno[state->n] = state->ob;
}