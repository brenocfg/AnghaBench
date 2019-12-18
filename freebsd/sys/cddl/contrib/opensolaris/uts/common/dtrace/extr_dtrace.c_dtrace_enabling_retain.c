#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dts_nretained; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_8__ {struct TYPE_8__* dten_prev; struct TYPE_8__* dten_next; TYPE_1__* dten_vstate; } ;
typedef  TYPE_3__ dtrace_enabling_t ;
struct TYPE_6__ {TYPE_2__* dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 scalar_t__ dtrace_retain_max ; 
 TYPE_3__* dtrace_retained ; 
 int /*<<< orphan*/  dtrace_retained_gen ; 

__attribute__((used)) static int
dtrace_enabling_retain(dtrace_enabling_t *enab)
{
	dtrace_state_t *state;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(enab->dten_next == NULL && enab->dten_prev == NULL);
	ASSERT(enab->dten_vstate != NULL);

	state = enab->dten_vstate->dtvs_state;
	ASSERT(state != NULL);

	/*
	 * We only allow each state to retain dtrace_retain_max enablings.
	 */
	if (state->dts_nretained >= dtrace_retain_max)
		return (ENOSPC);

	state->dts_nretained++;
	dtrace_retained_gen++;

	if (dtrace_retained == NULL) {
		dtrace_retained = enab;
		return (0);
	}

	enab->dten_next = dtrace_retained;
	dtrace_retained->dten_prev = enab;
	dtrace_retained = enab;

	return (0);
}