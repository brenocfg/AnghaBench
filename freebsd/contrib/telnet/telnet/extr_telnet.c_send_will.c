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
 int /*<<< orphan*/  WILL ; 
 scalar_t__ my_state_is_will (int) ; 
 scalar_t__ my_want_state_is_will (int) ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_my_want_state_will (int) ; 
 scalar_t__ telnetport ; 
 scalar_t__* will_wont_resp ; 

void
send_will(int c, int init)
{
    if (init) {
	if (((will_wont_resp[c] == 0) && my_state_is_will(c)) ||
				my_want_state_is_will(c))
	    return;
	set_my_want_state_will(c);
	will_wont_resp[c]++;
    }
    if (telnetport < 0)
	return;
    NET2ADD(IAC, WILL);
    NETADD(c);
    printoption("SENT", WILL, c);
}