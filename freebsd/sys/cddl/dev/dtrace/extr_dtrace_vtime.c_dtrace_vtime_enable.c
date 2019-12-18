#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int dtrace_vtime_state_t ;

/* Variables and functions */
#define  DTRACE_VTIME_ACTIVE 131 
#define  DTRACE_VTIME_ACTIVE_TNF 130 
#define  DTRACE_VTIME_INACTIVE 129 
#define  DTRACE_VTIME_INACTIVE_TNF 128 
 int dtrace_cas32 (int /*<<< orphan*/ *,int,int) ; 
 int dtrace_vtime_active ; 
 int /*<<< orphan*/  panic (char*) ; 

void
dtrace_vtime_enable(void)
{
	dtrace_vtime_state_t state, nstate = 0;

	do {
		state = dtrace_vtime_active;

		switch (state) {
		case DTRACE_VTIME_INACTIVE:
			nstate = DTRACE_VTIME_ACTIVE;
			break;

		case DTRACE_VTIME_INACTIVE_TNF:
			nstate = DTRACE_VTIME_ACTIVE_TNF;
			break;

		case DTRACE_VTIME_ACTIVE:
		case DTRACE_VTIME_ACTIVE_TNF:
			panic("DTrace virtual time already enabled");
			/*NOTREACHED*/
		}

	} while	(dtrace_cas32((uint32_t *)&dtrace_vtime_active,
	    state, nstate) != state);
}