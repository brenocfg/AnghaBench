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
 int TELOPT_TM ; 
 scalar_t__* do_dont_resp ; 
 scalar_t__ doopt ; 
 scalar_t__ his_state_is_will (int) ; 
 scalar_t__ his_want_state_is_will (int) ; 
 int /*<<< orphan*/  output_data (char const*,int) ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  set_his_want_state_will (int) ; 
 int /*<<< orphan*/  set_his_want_state_wont (int) ; 

void
send_do(int option, int init)
{
    if (init) {
	if ((do_dont_resp[option] == 0 && his_state_is_will(option)) ||
	    his_want_state_is_will(option))
	    return;
	/*
	 * Special case for TELOPT_TM:  We send a DO, but pretend
	 * that we sent a DONT, so that we can send more DOs if
	 * we want to.
	 */
	if (option == TELOPT_TM)
	    set_his_want_state_wont(option);
	else
	    set_his_want_state_will(option);
	do_dont_resp[option]++;
    }
    output_data((const char *)doopt, option);

    DIAG(TD_OPTIONS, printoption("td: send do", option));
}