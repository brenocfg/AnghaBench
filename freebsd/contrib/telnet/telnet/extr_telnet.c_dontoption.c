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
#define  TELOPT_LINEMODE 129 
#define  TELOPT_NEW_ENVIRON 128 
 int /*<<< orphan*/  TELOPT_OLD_ENVIRON ; 
 int /*<<< orphan*/  linemode ; 
 scalar_t__ my_state_is_will (int) ; 
 scalar_t__ my_state_is_wont (int) ; 
 scalar_t__ my_want_state_is_will (int) ; 
 int /*<<< orphan*/  send_will (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_wont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_my_state_wont (int) ; 
 int /*<<< orphan*/  set_my_want_state_wont (int) ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telopt_environ ; 
 scalar_t__* will_wont_resp ; 

__attribute__((used)) static void
dontoption(int option)
{

	if (will_wont_resp[option]) {
	    --will_wont_resp[option];
	    if (will_wont_resp[option] && my_state_is_wont(option))
		--will_wont_resp[option];
	}

	if ((will_wont_resp[option] == 0) && my_want_state_is_will(option)) {
	    switch (option) {
	    case TELOPT_LINEMODE:
		linemode = 0;	/* put us back to the default state */
		break;
#ifdef	OLD_ENVIRON
	    case TELOPT_NEW_ENVIRON:
		/*
		 * The new environ option wasn't recognized, try
		 * the old one.
		 */
		send_will(TELOPT_OLD_ENVIRON, 1);
		telopt_environ = TELOPT_OLD_ENVIRON;
		break;
#endif
	    }
	    /* we always accept a DONT */
	    set_my_want_state_wont(option);
	    if (my_state_is_will(option))
		send_wont(option, 0);
	    setconnmode(0);			/* Set new tty mode */
	}
	set_my_state_wont(option);
}