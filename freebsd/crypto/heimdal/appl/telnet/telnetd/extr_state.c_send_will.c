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
 scalar_t__ my_state_is_will (int) ; 
 scalar_t__ my_want_state_is_will (int) ; 
 int /*<<< orphan*/  output_data (char const*,int) ; 
 int /*<<< orphan*/  printoption (char*,int) ; 
 int /*<<< orphan*/  set_my_want_state_will (int) ; 
 scalar_t__ will ; 
 scalar_t__* will_wont_resp ; 

void
send_will(int option, int init)
{
    if (init) {
	if ((will_wont_resp[option] == 0 && my_state_is_will(option))||
	    my_want_state_is_will(option))
	    return;
	set_my_want_state_will(option);
	will_wont_resp[option]++;
    }
    output_data ((const char *)will, option);

    DIAG(TD_OPTIONS, printoption("td: send will", option));
}