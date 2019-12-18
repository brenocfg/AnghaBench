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
 int /*<<< orphan*/  LFLOW_OFF ; 
 int /*<<< orphan*/  LFLOW_ON ; 
 int /*<<< orphan*/  LFLOW_RESTART_ANY ; 
 int /*<<< orphan*/  LFLOW_RESTART_XON ; 
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SE ; 
 int /*<<< orphan*/  TELOPT_LFLOW ; 
 scalar_t__ flowmode ; 
 scalar_t__ his_state_is_will (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ restartany ; 
 scalar_t__ tty_flowmode () ; 
 scalar_t__ tty_restartany () ; 

void
flowstat(void)
{
    if (his_state_is_will(TELOPT_LFLOW)) {
	if (tty_flowmode() != flowmode) {
	    flowmode = tty_flowmode();
	    output_data("%c%c%c%c%c%c",
			IAC, SB, TELOPT_LFLOW,
			flowmode ? LFLOW_ON : LFLOW_OFF,
			IAC, SE);
	}
	if (tty_restartany() != restartany) {
	    restartany = tty_restartany();
	    output_data("%c%c%c%c%c%c",
			IAC, SB, TELOPT_LFLOW,
			restartany ? LFLOW_RESTART_ANY
			: LFLOW_RESTART_XON,
			IAC, SE);
	}
    }
}