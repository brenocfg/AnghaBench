#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_state {unsigned int cache_nr; TYPE_2__* untracked; TYPE_1__** cache; int /*<<< orphan*/  fsmonitor_last_update; int /*<<< orphan*/  cache_changed; } ;
struct TYPE_4__ {int use_fsmonitor; } ;
struct TYPE_3__ {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_FSMONITOR_VALID ; 
 int /*<<< orphan*/  FSMONITOR_CHANGED ; 
 int /*<<< orphan*/  add_untracked_cache (struct index_state*) ; 
 int /*<<< orphan*/  getnanotime () ; 
 int /*<<< orphan*/  refresh_fsmonitor (struct index_state*) ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*) ; 

void add_fsmonitor(struct index_state *istate)
{
	unsigned int i;

	if (!istate->fsmonitor_last_update) {
		trace_printf_key(&trace_fsmonitor, "add fsmonitor");
		istate->cache_changed |= FSMONITOR_CHANGED;
		istate->fsmonitor_last_update = getnanotime();

		/* reset the fsmonitor state */
		for (i = 0; i < istate->cache_nr; i++)
			istate->cache[i]->ce_flags &= ~CE_FSMONITOR_VALID;

		/* reset the untracked cache */
		if (istate->untracked) {
			add_untracked_cache(istate);
			istate->untracked->use_fsmonitor = 1;
		}

		/* Update the fsmonitor state */
		refresh_fsmonitor(istate);
	}
}