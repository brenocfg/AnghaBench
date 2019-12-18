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
 int /*<<< orphan*/  DIAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KLUDGE_LINEMODE ; 
 int /*<<< orphan*/  KLUDGE_OK ; 
 int /*<<< orphan*/  NO_AUTOKLUDGE ; 
 int /*<<< orphan*/  REAL_LINEMODE ; 
 int /*<<< orphan*/  SLC_DEFAULT ; 
 int /*<<< orphan*/  SLC_LEVELBITS ; 
 size_t SLC_XOFF ; 
 size_t SLC_XON ; 
 int /*<<< orphan*/  TD_OPTIONS ; 
#define  TELOPT_AUTHENTICATION 141 
#define  TELOPT_BINARY 140 
#define  TELOPT_ECHO 139 
#define  TELOPT_ENCRYPT 138 
#define  TELOPT_LFLOW 137 
#define  TELOPT_LINEMODE 136 
#define  TELOPT_NAWS 135 
#define  TELOPT_NEW_ENVIRON 134 
#define  TELOPT_OLD_ENVIRON 133 
#define  TELOPT_SGA 132 
#define  TELOPT_TM 131 
#define  TELOPT_TSPEED 130 
#define  TELOPT_TTYPE 129 
#define  TELOPT_XDISPLOC 128 
 int /*<<< orphan*/  WILL ; 
 int /*<<< orphan*/  auth_level ; 
 void auth_request () ; 
 int /*<<< orphan*/  clientstat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* do_dont_resp ; 
 void doclientstat () ; 
 void encrypt_send_support () ; 
 void flowstat () ; 
 scalar_t__ his_state_is_will (int) ; 
 scalar_t__ his_want_state_is_wont (int) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  lmodetype ; 
 int /*<<< orphan*/  not42 ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  send_do (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_dont (int,int) ; 
 int /*<<< orphan*/  send_wont (int,int) ; 
 int /*<<< orphan*/  set_his_state_will (int) ; 
 int /*<<< orphan*/  set_his_want_state_will (int) ; 
 int /*<<< orphan*/  set_termbuf () ; 
 TYPE_2__* slctab ; 
 void stub1 () ; 
 int /*<<< orphan*/  tty_binaryin (int) ; 

void
willoption(int option)
{
	int changeok = 0;
	void (*func)(void) = 0;

	/*
	 * process input from peer.
	 */

	DIAG(TD_OPTIONS, printoption("td: recv will", option));

	if (do_dont_resp[option]) {
		do_dont_resp[option]--;
		if (do_dont_resp[option] && his_state_is_will(option))
			do_dont_resp[option]--;
	}
	if (do_dont_resp[option] == 0) {
	    if (his_want_state_is_wont(option)) {
		switch (option) {

		case TELOPT_BINARY:
			init_termbuf();
			tty_binaryin(1);
			set_termbuf();
			changeok++;
			break;

		case TELOPT_ECHO:
			/*
			 * See comments below for more info.
			 */
			not42 = 0;	/* looks like a 4.2 system */
			break;

		case TELOPT_TM:
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
			/*
			 * This telnetd implementation does not really
			 * support timing marks, it just uses them to
			 * support the kludge linemode stuff.  If we
			 * receive a will or wont TM in response to our
			 * do TM request that may have been sent to
			 * determine kludge linemode support, process
			 * it, otherwise TM should get a negative
			 * response back.
			 */
			/*
			 * Handle the linemode kludge stuff.
			 * If we are not currently supporting any
			 * linemode at all, then we assume that this
			 * is the client telling us to use kludge
			 * linemode in response to our query.  Set the
			 * linemode type that is to be supported, note
			 * that the client wishes to use linemode, and
			 * eat the will TM as though it never arrived.
			 */
			if (lmodetype < KLUDGE_LINEMODE) {
				lmodetype = KLUDGE_LINEMODE;
				clientstat(TELOPT_LINEMODE, WILL, 0);
				send_wont(TELOPT_SGA, 1);
			} else if (lmodetype == NO_AUTOKLUDGE) {
				lmodetype = KLUDGE_OK;
			}
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
			/*
			 * We never respond to a WILL TM, and
			 * we leave the state WONT.
			 */
			return;

		case TELOPT_LFLOW:
			/*
			 * If we are going to support flow control
			 * option, then don't worry peer that we can't
			 * change the flow control characters.
			 */
			slctab[SLC_XON].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XON].defset.flag |= SLC_DEFAULT;
			slctab[SLC_XOFF].defset.flag &= ~SLC_LEVELBITS;
			slctab[SLC_XOFF].defset.flag |= SLC_DEFAULT;
		case TELOPT_TTYPE:
		case TELOPT_SGA:
		case TELOPT_NAWS:
		case TELOPT_TSPEED:
		case TELOPT_XDISPLOC:
		case TELOPT_NEW_ENVIRON:
		case TELOPT_OLD_ENVIRON:
			changeok++;
			break;

#ifdef	LINEMODE
		case TELOPT_LINEMODE:
# ifdef	KLUDGELINEMODE
			/*
			 * Note client's desire to use linemode.
			 */
			lmodetype = REAL_LINEMODE;
# endif	/* KLUDGELINEMODE */
			func = doclientstat;
			changeok++;
			break;
#endif	/* LINEMODE */

#ifdef	AUTHENTICATION
		case TELOPT_AUTHENTICATION:
			if (auth_level >= 0) {
				func = auth_request;
				changeok++;
			}
			break;
#endif

#ifdef	ENCRYPTION
		case TELOPT_ENCRYPT:
			func = encrypt_send_support;
			changeok++;
			break;
#endif	/* ENCRYPTION */

		default:
			break;
		}
		if (changeok) {
			set_his_want_state_will(option);
			send_do(option, 0);
		} else {
			do_dont_resp[option]++;
			send_dont(option, 0);
		}
	    } else {
		/*
		 * Option processing that should happen when
		 * we receive conformation of a change in
		 * state that we had requested.
		 */
		switch (option) {
		case TELOPT_ECHO:
			not42 = 0;	/* looks like a 4.2 system */
			/*
			 * Egads, he responded "WILL ECHO".  Turn
			 * it off right now!
			 */
			send_dont(option, 1);
			/*
			 * "WILL ECHO".  Kludge upon kludge!
			 * A 4.2 client is now echoing user input at
			 * the tty.  This is probably undesireable and
			 * it should be stopped.  The client will
			 * respond WONT TM to the DO TM that we send to
			 * check for kludge linemode.  When the WONT TM
			 * arrives, linemode will be turned off and a
			 * change propogated to the pty.  This change
			 * will cause us to process the new pty state
			 * in localstat(), which will notice that
			 * linemode is off and send a WILL ECHO
			 * so that we are properly in character mode and
			 * all is well.
			 */
			break;
#ifdef	LINEMODE
		case TELOPT_LINEMODE:
# ifdef	KLUDGELINEMODE
			/*
			 * Note client's desire to use linemode.
			 */
			lmodetype = REAL_LINEMODE;
# endif	/* KLUDGELINEMODE */
			func = doclientstat;
			break;
#endif	/* LINEMODE */

#ifdef	AUTHENTICATION
		case TELOPT_AUTHENTICATION:
			func = auth_request;
			break;
#endif

#ifdef	ENCRYPTION
		case TELOPT_ENCRYPT:
			func = encrypt_send_support;
			break;
#endif	/* ENCRYPTION */
		case TELOPT_LFLOW:
			func = flowstat;
			break;
		}
	    }
	}
	set_his_state_will(option);
	if (func)
		(*func)();
}