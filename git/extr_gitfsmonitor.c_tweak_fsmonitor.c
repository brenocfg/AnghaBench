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
struct index_state {int cache_nr; int /*<<< orphan*/ * fsmonitor_dirty; TYPE_1__* untracked; TYPE_2__** cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  ce_flags; } ;
struct TYPE_3__ {int use_fsmonitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_FSMONITOR_VALID ; 
 int /*<<< orphan*/  add_fsmonitor (struct index_state*) ; 
 int /*<<< orphan*/  ewah_each_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct index_state*) ; 
 int /*<<< orphan*/  ewah_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsmonitor_ewah_callback ; 
 int git_config_get_fsmonitor () ; 
 int /*<<< orphan*/  remove_fsmonitor (struct index_state*) ; 

void tweak_fsmonitor(struct index_state *istate)
{
	int i;
	int fsmonitor_enabled = git_config_get_fsmonitor();

	if (istate->fsmonitor_dirty) {
		if (fsmonitor_enabled) {
			/* Mark all entries valid */
			for (i = 0; i < istate->cache_nr; i++) {
				istate->cache[i]->ce_flags |= CE_FSMONITOR_VALID;
			}

			/* Mark all previously saved entries as dirty */
			ewah_each_bit(istate->fsmonitor_dirty, fsmonitor_ewah_callback, istate);

			/* Now mark the untracked cache for fsmonitor usage */
			if (istate->untracked)
				istate->untracked->use_fsmonitor = 1;
		}

		ewah_free(istate->fsmonitor_dirty);
		istate->fsmonitor_dirty = NULL;
	}

	switch (fsmonitor_enabled) {
	case -1: /* keep: do nothing */
		break;
	case 0: /* false */
		remove_fsmonitor(istate);
		break;
	case 1: /* true */
		add_fsmonitor(istate);
		break;
	default: /* unknown value: do nothing */
		break;
	}
}