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
 int /*<<< orphan*/  DIAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KLUDGE_LINEMODE ; 
 int /*<<< orphan*/  NO_LINEMODE ; 
 int /*<<< orphan*/  TD_OPTIONS ; 
#define  TELOPT_BINARY 142 
#define  TELOPT_ECHO 141 
#define  TELOPT_ENCRYPT 140 
#define  TELOPT_LFLOW 139 
#define  TELOPT_LINEMODE 138 
#define  TELOPT_LOGOUT 137 
#define  TELOPT_NAWS 136 
#define  TELOPT_NEW_ENVIRON 135 
#define  TELOPT_OLD_ENVIRON 134 
#define  TELOPT_SGA 133 
#define  TELOPT_STATUS 132 
#define  TELOPT_TM 131 
#define  TELOPT_TSPEED 130 
#define  TELOPT_TTYPE 129 
#define  TELOPT_XDISPLOC 128 
 int /*<<< orphan*/  WONT ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clientstat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  his_state_is_wont (int) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  linemode ; 
 int /*<<< orphan*/  lmodetype ; 
 scalar_t__ my_state_is_will (int) ; 
 scalar_t__ my_want_state_is_wont (int) ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  send_will (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_wont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_my_state_will (int const) ; 
 int /*<<< orphan*/  set_my_state_wont (int) ; 
 int /*<<< orphan*/  set_my_want_state_will (int const) ; 
 int /*<<< orphan*/  set_my_want_state_wont (int) ; 
 int /*<<< orphan*/  set_termbuf () ; 
 int /*<<< orphan*/  tty_binaryout (int) ; 
 int /*<<< orphan*/  tty_setecho (int) ; 
 int /*<<< orphan*/  turn_on_sga ; 
 scalar_t__* will_wont_resp ; 

void
dooption(int option)
{
	int changeok = 0;

	/*
	 * Process client input.
	 */

	DIAG(TD_OPTIONS, printoption("td: recv do", option));

	if (will_wont_resp[option]) {
		will_wont_resp[option]--;
		if (will_wont_resp[option] && my_state_is_will(option))
			will_wont_resp[option]--;
	}
	if ((will_wont_resp[option] == 0) && (my_want_state_is_wont(option))) {
		switch (option) {
		case TELOPT_ECHO:
#ifdef	LINEMODE
# ifdef	KLUDGELINEMODE
			if (lmodetype == NO_LINEMODE)
# else
			if (his_state_is_wont(TELOPT_LINEMODE))
# endif
#endif
			{
				init_termbuf();
				tty_setecho(1);
				set_termbuf();
			}
			changeok++;
			break;

		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryout(1);
			set_termbuf();
			changeok++;
			break;

		case TELOPT_SGA:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			/*
			 * If kludge linemode is in use, then we must
			 * process an incoming do SGA for linemode
			 * purposes.
			 */
			if (lmodetype == KLUDGE_LINEMODE) {
				/*
				 * Receipt of "do SGA" in kludge
				 * linemode is the peer asking us to
				 * turn off linemode.  Make note of
				 * the request.
				 */
				clientstat(TELOPT_LINEMODE, WONT, 0);
				/*
				 * If linemode did not get turned off
				 * then don't tell peer that we did.
				 * Breaking here forces a wont SGA to
				 * be returned.
				 */
				if (linemode)
					break;
			}
#else
			turn_on_sga = 0;
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
			changeok++;
			break;

		case TELOPT_STATUS:
			changeok++;
			break;

		case TELOPT_TM:
			/*
			 * Special case for TM.  We send a WILL, but
			 * pretend we sent a WONT.
			 */
			send_will(option, 0);
			set_my_want_state_wont(option);
			set_my_state_wont(option);
			return;

		case TELOPT_LOGOUT:
			/*
			 * When we get a LOGOUT option, respond
			 * with a WILL LOGOUT, make sure that
			 * it gets written out to the network,
			 * and then just go away...
			 */
			set_my_want_state_will(TELOPT_LOGOUT);
			send_will(TELOPT_LOGOUT, 0);
			set_my_state_will(TELOPT_LOGOUT);
			(void)netflush();
			cleanup(0);
			/* NOT REACHED */
			break;

#ifdef	ENCRYPTION
		case TELOPT_ENCRYPT:
			changeok++;
			break;
#endif	/* ENCRYPTION */
		case TELOPT_LINEMODE:
		case TELOPT_TTYPE:
		case TELOPT_NAWS:
		case TELOPT_TSPEED:
		case TELOPT_LFLOW:
		case TELOPT_XDISPLOC:
#ifdef	TELOPT_ENVIRON
		case TELOPT_NEW_ENVIRON:
#endif
		case TELOPT_OLD_ENVIRON:
		default:
			break;
		}
		if (changeok) {
			set_my_want_state_will(option);
			send_will(option, 0);
		} else {
			will_wont_resp[option]++;
			send_wont(option, 0);
		}
	}
	set_my_state_will(option);

}