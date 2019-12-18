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
 scalar_t__* do_dont_resp ; 
 scalar_t__ dont ; 
 scalar_t__ his_state_is_wont (int) ; 
 scalar_t__ his_want_state_is_wont (int) ; 
 int /*<<< orphan*/  output_data (char const*,int) ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  set_his_want_state_wont (int) ; 

void
send_dont(int option, int init)
{
    if (init) {
	if ((do_dont_resp[option] == 0 && his_state_is_wont(option)) ||
	    his_want_state_is_wont(option))
	    return;
	set_his_want_state_wont(option);
	do_dont_resp[option]++;
    }
    output_data((const char *)dont, option);

    DIAG(TD_OPTIONS, printoption("td: send dont", option));
}