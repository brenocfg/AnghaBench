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
#define  TELOPT_AUTHENTICATION 135 
#define  TELOPT_BINARY 134 
#define  TELOPT_ECHO 133 
#define  TELOPT_ENCRYPT 132 
#define  TELOPT_LINEMODE 131 
#define  TELOPT_SGA 130 
#define  TELOPT_STATUS 129 
#define  TELOPT_TM 128 
 scalar_t__* do_dont_resp ; 
 int /*<<< orphan*/  encrypt_send_support () ; 
 int /*<<< orphan*/  flushout ; 
 int /*<<< orphan*/  modenegotiated ; 
 scalar_t__ my_state_is_do (int) ; 
 scalar_t__ my_want_state_is_dont (int) ; 
 int /*<<< orphan*/  send_do (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_dont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_my_state_do (int) ; 
 int /*<<< orphan*/  set_my_state_dont (int) ; 
 int /*<<< orphan*/  set_my_want_state_do (int) ; 
 int /*<<< orphan*/  set_my_want_state_dont (int) ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settimer (int /*<<< orphan*/ ) ; 

void
willoption(int option)
{
	int new_state_ok = 0;

	if (do_dont_resp[option]) {
	    --do_dont_resp[option];
	    if (do_dont_resp[option] && my_state_is_do(option))
		--do_dont_resp[option];
	}

	if ((do_dont_resp[option] == 0) && my_want_state_is_dont(option)) {

	    switch (option) {

	    case TELOPT_ECHO:
	    case TELOPT_BINARY:
	    case TELOPT_SGA:
		settimer(modenegotiated);
		/* FALL THROUGH */
	    case TELOPT_STATUS:
#if	defined(AUTHENTICATION)
	    case TELOPT_AUTHENTICATION:
#endif
#if	defined(ENCRYPTION)
	    case TELOPT_ENCRYPT:
#endif
		new_state_ok = 1;
		break;

	    case TELOPT_TM:
		if (flushout)
		    flushout = 0;
		/*
		 * Special case for TM.  If we get back a WILL,
		 * pretend we got back a WONT.
		 */
		set_my_want_state_dont(option);
		set_my_state_dont(option);
		return;			/* Never reply to TM will's/wont's */

	    case TELOPT_LINEMODE:
	    default:
		break;
	    }

	    if (new_state_ok) {
		set_my_want_state_do(option);
		send_do(option, 0);
		setconnmode(0);		/* possibly set new tty mode */
	    } else {
		do_dont_resp[option]++;
		send_dont(option, 0);
	    }
	}
	set_my_state_do(option);
#if	defined(ENCRYPTION)
	if (option == TELOPT_ENCRYPT)
		encrypt_send_support();
#endif
}