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
 int /*<<< orphan*/  TD_OPTIONS ; 
#define  TELOPT_BINARY 130 
#define  TELOPT_ECHO 129 
#define  TELOPT_SGA 128 
 int /*<<< orphan*/  init_termbuf () ; 
 scalar_t__ my_state_is_will (int) ; 
 scalar_t__ my_state_is_wont (int) ; 
 scalar_t__ my_want_state_is_will (int) ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  send_will (int,int) ; 
 int /*<<< orphan*/  send_wont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_my_state_wont (int) ; 
 int /*<<< orphan*/  set_my_want_state_wont (int) ; 
 int /*<<< orphan*/  set_termbuf () ; 
 int /*<<< orphan*/  tty_binaryout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_setecho (int /*<<< orphan*/ ) ; 
 int turn_on_sga ; 
 scalar_t__* will_wont_resp ; 

void
dontoption(int option)
{
    /*
     * Process client input.
	 */


    DIAG(TD_OPTIONS, printoption("td: recv dont", option));

    if (will_wont_resp[option]) {
	will_wont_resp[option]--;
	if (will_wont_resp[option] && my_state_is_wont(option))
	    will_wont_resp[option]--;
    }
    if ((will_wont_resp[option] == 0) && (my_want_state_is_will(option))) {
	switch (option) {
	case TELOPT_BINARY:
	    init_termbuf();
	    tty_binaryout(0);
	    set_termbuf();
	    break;

	case TELOPT_ECHO:	/* we should stop echoing */
	    {
		init_termbuf();
		tty_setecho(0);
		set_termbuf();
	    }
	break;

	case TELOPT_SGA:
	    set_my_want_state_wont(option);
	    if (my_state_is_will(option))
		send_wont(option, 0);
	    set_my_state_wont(option);
	    if (turn_on_sga ^= 1)
		send_will(option, 1);
	    return;

	default:
	    break;
	}

	set_my_want_state_wont(option);
	if (my_state_is_will(option))
	    send_wont(option, 0);
    }
    set_my_state_wont(option);

}