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
struct TYPE_5__ {int dts_nspeculations; int /*<<< orphan*/  dts_aggbuffer; int /*<<< orphan*/  dts_buffer; TYPE_2__* dts_speculations; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  dtsp_buffer; } ;
typedef  TYPE_2__ dtrace_speculation_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEOPT_AGGSIZE ; 
 int /*<<< orphan*/  DTRACEOPT_BUFSIZE ; 
 int /*<<< orphan*/  DTRACEOPT_SPECSIZE ; 
 int dtrace_state_buffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_state_buffers(dtrace_state_t *state)
{
	dtrace_speculation_t *spec = state->dts_speculations;
	int rval, i;

	if ((rval = dtrace_state_buffer(state, state->dts_buffer,
	    DTRACEOPT_BUFSIZE)) != 0)
		return (rval);

	if ((rval = dtrace_state_buffer(state, state->dts_aggbuffer,
	    DTRACEOPT_AGGSIZE)) != 0)
		return (rval);

	for (i = 0; i < state->dts_nspeculations; i++) {
		if ((rval = dtrace_state_buffer(state,
		    spec[i].dtsp_buffer, DTRACEOPT_SPECSIZE)) != 0)
			return (rval);
	}

	return (0);
}