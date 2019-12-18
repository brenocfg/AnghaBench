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
 int /*<<< orphan*/  SLC_DEFAULT ; 
 int /*<<< orphan*/  SLC_LEVELBITS ; 
 size_t SLC_XOFF ; 
 size_t SLC_XON ; 
 int /*<<< orphan*/  TD_OPTIONS ; 
#define  TELOPT_AUTHENTICATION 140 
#define  TELOPT_BINARY 139 
#define  TELOPT_ECHO 138 
#define  TELOPT_ENCRYPT 137 
#define  TELOPT_LFLOW 136 
#define  TELOPT_NAWS 135 
#define  TELOPT_NEW_ENVIRON 134 
#define  TELOPT_OLD_ENVIRON 133 
#define  TELOPT_SGA 132 
#define  TELOPT_TM 131 
#define  TELOPT_TSPEED 130 
#define  TELOPT_TTYPE 129 
#define  TELOPT_XDISPLOC 128 
 void auth_request () ; 
 scalar_t__* do_dont_resp ; 
 void encrypt_send_support () ; 
 void flowstat () ; 
 scalar_t__ his_state_is_will (int) ; 
 scalar_t__ his_want_state_is_wont (int) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  not42 ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  send_do (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_dont (int,int) ; 
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
    void (*func)(void) = NULL;

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


#ifdef	AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
		func = auth_request;
		changeok++;
		break;
#endif

#ifdef	ENCRYPTION
	    case TELOPT_ENCRYPT:
		func = encrypt_send_support;
		changeok++;
		break;
#endif

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

#ifdef	AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
		func = auth_request;
		break;
#endif

#ifdef	ENCRYPTION
	    case TELOPT_ENCRYPT:
		func = encrypt_send_support;
		break;
#endif

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