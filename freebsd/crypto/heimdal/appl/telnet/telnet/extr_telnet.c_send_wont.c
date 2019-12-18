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
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  NET2ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETADD (int) ; 
 int /*<<< orphan*/  WONT ; 
 scalar_t__ my_state_is_wont (int) ; 
 scalar_t__ my_want_state_is_wont (int) ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_my_want_state_wont (int) ; 
 scalar_t__* will_wont_resp ; 

void
send_wont(int c, int init)
{
    if (init) {
	if (((will_wont_resp[c] == 0) && my_state_is_wont(c)) ||
				my_want_state_is_wont(c))
	    return;
	set_my_want_state_wont(c);
	will_wont_resp[c]++;
    }
    NET2ADD(IAC, WONT);
    NETADD(c);
    printoption("SENT", WONT, c);
}