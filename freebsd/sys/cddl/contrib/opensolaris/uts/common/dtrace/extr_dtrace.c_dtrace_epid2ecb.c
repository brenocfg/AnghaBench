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
struct TYPE_5__ {int dts_necbs; TYPE_2__** dts_ecbs; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int dtrace_epid_t ;
struct TYPE_6__ {int dte_epid; } ;
typedef  TYPE_2__ dtrace_ecb_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static dtrace_ecb_t *
dtrace_epid2ecb(dtrace_state_t *state, dtrace_epid_t id)
{
	dtrace_ecb_t *ecb;

	ASSERT(MUTEX_HELD(&dtrace_lock));

	if (id == 0 || id > state->dts_necbs)
		return (NULL);

	ASSERT(state->dts_necbs > 0 && state->dts_ecbs != NULL);
	ASSERT((ecb = state->dts_ecbs[id - 1]) == NULL || ecb->dte_epid == id);

	return (state->dts_ecbs[id - 1]);
}