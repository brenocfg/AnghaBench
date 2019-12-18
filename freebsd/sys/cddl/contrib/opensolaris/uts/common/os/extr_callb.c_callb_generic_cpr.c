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
typedef  int clock_t ;
struct TYPE_2__ {int cc_events; int /*<<< orphan*/  cc_lockp; int /*<<< orphan*/  cc_stop_cv; int /*<<< orphan*/  cc_callb_cv; } ;
typedef  TYPE_1__ callb_cpr_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int CALLB_CPR_SAFE ; 
 int CALLB_CPR_START ; 
#define  CB_CODE_CPR_CHKPT 129 
#define  CB_CODE_CPR_RESUME 128 
 int /*<<< orphan*/  TR_CLOCK_TICK ; 
 int callb_timeout_sec ; 
 int cv_reltimedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ ) ; 

boolean_t
callb_generic_cpr(void *arg, int code)
{
	callb_cpr_t *cp = (callb_cpr_t *)arg;
	clock_t ret = 0;			/* assume success */

	mutex_enter(cp->cc_lockp);

	switch (code) {
	case CB_CODE_CPR_CHKPT:
		cp->cc_events |= CALLB_CPR_START;
#ifdef CPR_NOT_THREAD_SAFE
		while (!(cp->cc_events & CALLB_CPR_SAFE))
			/* cv_timedwait() returns -1 if it times out. */
			if ((ret = cv_reltimedwait(&cp->cc_callb_cv,
			    cp->cc_lockp, (callb_timeout_sec * hz),
			    TR_CLOCK_TICK)) == -1)
				break;
#endif
		break;

	case CB_CODE_CPR_RESUME:
		cp->cc_events &= ~CALLB_CPR_START;
		cv_signal(&cp->cc_stop_cv);
		break;
	}
	mutex_exit(cp->cc_lockp);
	return (ret != -1);
}