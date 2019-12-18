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
struct combine_diff_state {int /*<<< orphan*/  lno; int /*<<< orphan*/  nmask; TYPE_1__* sline; int /*<<< orphan*/  n; int /*<<< orphan*/  lost_bucket; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_lost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void consume_line(void *state_, char *line, unsigned long len)
{
	struct combine_diff_state *state = state_;
	if (!state->lost_bucket)
		return; /* not in any hunk yet */
	switch (line[0]) {
	case '-':
		append_lost(state->lost_bucket, state->n, line+1, len-1);
		break;
	case '+':
		state->sline[state->lno-1].flag |= state->nmask;
		state->lno++;
		break;
	}
}