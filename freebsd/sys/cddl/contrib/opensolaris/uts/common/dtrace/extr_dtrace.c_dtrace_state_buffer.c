#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int processorid_t ;
struct TYPE_4__ {int* dts_options; scalar_t__ dts_activity; int dts_reserve; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int dtrace_optval_t ;
typedef  int /*<<< orphan*/  dtrace_buffer_t ;
struct TYPE_5__ {TYPE_1__* dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACEBUF_FILL ; 
 int DTRACEBUF_INACTIVE ; 
 int DTRACEBUF_NOSWITCH ; 
 int DTRACEBUF_RING ; 
 size_t DTRACEOPT_BUFPOLICY ; 
 int DTRACEOPT_BUFPOLICY_FILL ; 
 int DTRACEOPT_BUFPOLICY_RING ; 
 size_t DTRACEOPT_BUFRESIZE ; 
 int DTRACEOPT_BUFRESIZE_MANUAL ; 
 int DTRACEOPT_BUFSIZE ; 
 size_t DTRACEOPT_CPU ; 
 int DTRACEOPT_MAX ; 
 int DTRACEOPT_SPECSIZE ; 
 int DTRACEOPT_UNSET ; 
 scalar_t__ DTRACE_ACTIVITY_ACTIVE ; 
 scalar_t__ DTRACE_ACTIVITY_INACTIVE ; 
 int E2BIG ; 
 int ENOMEM ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_lock ; 
 TYPE_3__ dtrace_anon ; 
 int dtrace_buffer_alloc (int /*<<< orphan*/ *,int,int,int,int*) ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static int
dtrace_state_buffer(dtrace_state_t *state, dtrace_buffer_t *buf, int which)
{
	dtrace_optval_t *opt = state->dts_options, size;
	processorid_t cpu = 0;;
	int flags = 0, rval, factor, divisor = 1;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(MUTEX_HELD(&cpu_lock));
	ASSERT(which < DTRACEOPT_MAX);
	ASSERT(state->dts_activity == DTRACE_ACTIVITY_INACTIVE ||
	    (state == dtrace_anon.dta_state &&
	    state->dts_activity == DTRACE_ACTIVITY_ACTIVE));

	if (opt[which] == DTRACEOPT_UNSET || opt[which] == 0)
		return (0);

	if (opt[DTRACEOPT_CPU] != DTRACEOPT_UNSET)
		cpu = opt[DTRACEOPT_CPU];

	if (which == DTRACEOPT_SPECSIZE)
		flags |= DTRACEBUF_NOSWITCH;

	if (which == DTRACEOPT_BUFSIZE) {
		if (opt[DTRACEOPT_BUFPOLICY] == DTRACEOPT_BUFPOLICY_RING)
			flags |= DTRACEBUF_RING;

		if (opt[DTRACEOPT_BUFPOLICY] == DTRACEOPT_BUFPOLICY_FILL)
			flags |= DTRACEBUF_FILL;

		if (state != dtrace_anon.dta_state ||
		    state->dts_activity != DTRACE_ACTIVITY_ACTIVE)
			flags |= DTRACEBUF_INACTIVE;
	}

	for (size = opt[which]; size >= sizeof (uint64_t); size /= divisor) {
		/*
		 * The size must be 8-byte aligned.  If the size is not 8-byte
		 * aligned, drop it down by the difference.
		 */
		if (size & (sizeof (uint64_t) - 1))
			size -= size & (sizeof (uint64_t) - 1);

		if (size < state->dts_reserve) {
			/*
			 * Buffers always must be large enough to accommodate
			 * their prereserved space.  We return E2BIG instead
			 * of ENOMEM in this case to allow for user-level
			 * software to differentiate the cases.
			 */
			return (E2BIG);
		}

		rval = dtrace_buffer_alloc(buf, size, flags, cpu, &factor);

		if (rval != ENOMEM) {
			opt[which] = size;
			return (rval);
		}

		if (opt[DTRACEOPT_BUFRESIZE] == DTRACEOPT_BUFRESIZE_MANUAL)
			return (rval);

		for (divisor = 2; divisor < factor; divisor <<= 1)
			continue;
	}

	return (ENOMEM);
}