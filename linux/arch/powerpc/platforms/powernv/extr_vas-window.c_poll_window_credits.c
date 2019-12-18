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
typedef  scalar_t__ u64 ;
struct vas_window {int wcreds_max; scalar_t__ tx_win; } ;

/* Variables and functions */
 int GET_FIELD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LRX_WCRED ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  TX_WCRED ; 
 int /*<<< orphan*/  VAS_LRX_WCRED ; 
 int /*<<< orphan*/  VAS_TX_WCRED ; 
 int /*<<< orphan*/  VAS_WINCTL_RX_WCRED_MODE ; 
 int /*<<< orphan*/  VAS_WINCTL_TX_WCRED_MODE ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINCTL ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ read_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_window_credits(struct vas_window *window)
{
	u64 val;
	int creds, mode;

	val = read_hvwc_reg(window, VREG(WINCTL));
	if (window->tx_win)
		mode = GET_FIELD(VAS_WINCTL_TX_WCRED_MODE, val);
	else
		mode = GET_FIELD(VAS_WINCTL_RX_WCRED_MODE, val);

	if (!mode)
		return;
retry:
	if (window->tx_win) {
		val = read_hvwc_reg(window, VREG(TX_WCRED));
		creds = GET_FIELD(VAS_TX_WCRED, val);
	} else {
		val = read_hvwc_reg(window, VREG(LRX_WCRED));
		creds = GET_FIELD(VAS_LRX_WCRED, val);
	}

	if (creds < window->wcreds_max) {
		val = 0;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(10));
		goto retry;
	}
}