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
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct TYPE_4__ {TYPE_1__ defset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_REJECT ; 
 int /*<<< orphan*/  DIAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CANTCHANGE ; 
 int /*<<< orphan*/  SLC_LEVELBITS ; 
 size_t SLC_XOFF ; 
 size_t SLC_XON ; 
 int /*<<< orphan*/  TD_OPTIONS ; 
#define  TELOPT_AUTHENTICATION 137 
#define  TELOPT_BINARY 136 
#define  TELOPT_ECHO 135 
#define  TELOPT_LFLOW 134 
#define  TELOPT_NEW_ENVIRON 133 
#define  TELOPT_OLD_ENVIRON 132 
#define  TELOPT_TM 131 
#define  TELOPT_TSPEED 130 
#define  TELOPT_TTYPE 129 
#define  TELOPT_XDISPLOC 128 
 int /*<<< orphan*/  auth_finished (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* do_dont_resp ; 
 int /*<<< orphan*/  environsubopt ; 
 scalar_t__ his_state_is_will (int) ; 
 scalar_t__ his_state_is_wont (int) ; 
 scalar_t__ his_want_state_is_will (int) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int not42 ; 
 int /*<<< orphan*/  oenvironsubopt ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  send_dont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_his_state_wont (int) ; 
 int /*<<< orphan*/  set_his_want_state_wont (int const) ; 
 int /*<<< orphan*/  set_termbuf () ; 
 int /*<<< orphan*/  settimer (int /*<<< orphan*/ ) ; 
 TYPE_2__* slctab ; 
 int /*<<< orphan*/  tspeedsubopt ; 
 int /*<<< orphan*/  tty_binaryin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttypesubopt ; 
 int /*<<< orphan*/  xdisplocsubopt ; 

void
wontoption(int option)
{
    /*
     * Process client input.
	 */

    DIAG(TD_OPTIONS, printoption("td: recv wont", option));

    if (do_dont_resp[option]) {
	do_dont_resp[option]--;
	if (do_dont_resp[option] && his_state_is_wont(option))
	    do_dont_resp[option]--;
    }
    if (do_dont_resp[option] == 0) {
	if (his_want_state_is_will(option)) {
	    /* it is always ok to change to negative state */
	    switch (option) {
	    case TELOPT_ECHO:
		not42 = 1; /* doesn't seem to be a 4.2 system */
		break;

	    case TELOPT_BINARY:
		init_termbuf();
		tty_binaryin(0);
		set_termbuf();
		break;

	    case TELOPT_TM:
		/*
		 * If we get a WONT TM, and had sent a DO TM,
		 * don't respond with a DONT TM, just leave it
		 * as is.  Short circut the state machine to
		 * achive this.
		 */
		set_his_want_state_wont(TELOPT_TM);
		return;

	    case TELOPT_LFLOW:
		/*
		 * If we are not going to support flow control
		 * option, then let peer know that we can't
		 * change the flow control characters.
		 */
		slctab[SLC_XON].defset.flag &= ~SLC_LEVELBITS;
		slctab[SLC_XON].defset.flag |= SLC_CANTCHANGE;
		slctab[SLC_XOFF].defset.flag &= ~SLC_LEVELBITS;
		slctab[SLC_XOFF].defset.flag |= SLC_CANTCHANGE;
		break;

#ifdef AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
		auth_finished(0, AUTH_REJECT);
		break;
#endif

		/*
		 * For options that we might spin waiting for
		 * sub-negotiation, if the client turns off the
		 * option rather than responding to the request,
		 * we have to treat it here as if we got a response
		 * to the sub-negotiation, (by updating the timers)
		 * so that we'll break out of the loop.
		 */
	    case TELOPT_TTYPE:
		settimer(ttypesubopt);
		break;

	    case TELOPT_TSPEED:
		settimer(tspeedsubopt);
		break;

	    case TELOPT_XDISPLOC:
		settimer(xdisplocsubopt);
		break;

	    case TELOPT_OLD_ENVIRON:
		settimer(oenvironsubopt);
		break;

	    case TELOPT_NEW_ENVIRON:
		settimer(environsubopt);
		break;

	    default:
		break;
	    }
	    set_his_want_state_wont(option);
	    if (his_state_is_will(option))
		send_dont(option, 0);
	} else {
	    switch (option) {
	    case TELOPT_TM:
		break;

#ifdef AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
		auth_finished(0, AUTH_REJECT);
		break;
#endif
	    default:
		break;
	    }
	}
    }
    set_his_state_wont(option);

}