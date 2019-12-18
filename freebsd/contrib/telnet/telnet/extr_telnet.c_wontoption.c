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

/* Variables and functions */
#define  TELOPT_ECHO 130 
#define  TELOPT_SGA 129 
#define  TELOPT_TM 128 
 scalar_t__* do_dont_resp ; 
 scalar_t__ flushout ; 
 int /*<<< orphan*/  kludgelinemode ; 
 int /*<<< orphan*/  modenegotiated ; 
 scalar_t__ my_state_is_do (int) ; 
 scalar_t__ my_state_is_dont (int) ; 
 scalar_t__ my_want_state_is_do (int) ; 
 int /*<<< orphan*/  send_dont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_my_state_dont (int) ; 
 int /*<<< orphan*/  set_my_want_state_dont (int) ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settimer (int /*<<< orphan*/ ) ; 

void
wontoption(int option)
{
	if (do_dont_resp[option]) {
	    --do_dont_resp[option];
	    if (do_dont_resp[option] && my_state_is_dont(option))
		--do_dont_resp[option];
	}

	if ((do_dont_resp[option] == 0) && my_want_state_is_do(option)) {

	    switch (option) {

#ifdef	KLUDGELINEMODE
	    case TELOPT_SGA:
		if (!kludgelinemode)
		    break;
		/* FALLTHROUGH */
#endif
	    case TELOPT_ECHO:
		settimer(modenegotiated);
		break;

	    case TELOPT_TM:
		if (flushout)
		    flushout = 0;
		set_my_want_state_dont(option);
		set_my_state_dont(option);
		return;		/* Never reply to TM will's/wont's */

	    default:
		break;
	    }
	    set_my_want_state_dont(option);
	    if (my_state_is_do(option))
		send_dont(option, 0);
	    setconnmode(0);			/* Set new tty mode */
	} else if (option == TELOPT_TM) {
	    /*
	     * Special case for TM.
	     */
	    if (flushout)
		flushout = 0;
	    set_my_want_state_dont(option);
	}
	set_my_state_dont(option);
}