#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dcr_destructive; } ;
struct TYPE_5__ {scalar_t__ dts_activity; scalar_t__* dts_options; TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
typedef  scalar_t__ dtrace_optval_t ;
typedef  int dtrace_optid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  DTRACEOPT_AGGSIZE 133 
#define  DTRACEOPT_BUFSIZE 132 
 int DTRACEOPT_CPU ; 
#define  DTRACEOPT_DESTRUCTIVE 131 
#define  DTRACEOPT_DYNVARSIZE 130 
 int DTRACEOPT_MAX ; 
#define  DTRACEOPT_SPECSIZE 129 
#define  DTRACEOPT_STRSIZE 128 
 scalar_t__ DTRACE_ACTIVITY_INACTIVE ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_destructive_disallow ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static int
dtrace_state_option(dtrace_state_t *state, dtrace_optid_t option,
    dtrace_optval_t val)
{
	ASSERT(MUTEX_HELD(&dtrace_lock));

	if (state->dts_activity != DTRACE_ACTIVITY_INACTIVE)
		return (EBUSY);

	if (option >= DTRACEOPT_MAX)
		return (EINVAL);

	if (option != DTRACEOPT_CPU && val < 0)
		return (EINVAL);

	switch (option) {
	case DTRACEOPT_DESTRUCTIVE:
		if (dtrace_destructive_disallow)
			return (EACCES);

		state->dts_cred.dcr_destructive = 1;
		break;

	case DTRACEOPT_BUFSIZE:
	case DTRACEOPT_DYNVARSIZE:
	case DTRACEOPT_AGGSIZE:
	case DTRACEOPT_SPECSIZE:
	case DTRACEOPT_STRSIZE:
		if (val < 0)
			return (EINVAL);

		if (val >= LONG_MAX) {
			/*
			 * If this is an otherwise negative value, set it to
			 * the highest multiple of 128m less than LONG_MAX.
			 * Technically, we're adjusting the size without
			 * regard to the buffer resizing policy, but in fact,
			 * this has no effect -- if we set the buffer size to
			 * ~LONG_MAX and the buffer policy is ultimately set to
			 * be "manual", the buffer allocation is guaranteed to
			 * fail, if only because the allocation requires two
			 * buffers.  (We set the the size to the highest
			 * multiple of 128m because it ensures that the size
			 * will remain a multiple of a megabyte when
			 * repeatedly halved -- all the way down to 15m.)
			 */
			val = LONG_MAX - (1 << 27) + 1;
		}
	}

	state->dts_options[option] = val;

	return (0);
}