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
struct p2p_data {int p2p_scan_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_SCAN_TIMEOUT ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_continue_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_scan_timeout ; 

void p2p_notify_scan_trigger_status(struct p2p_data *p2p, int status)
{
	if (status != 0) {
		p2p_dbg(p2p, "Scan request failed");
		/* Do continue find even for the first p2p_find_scan */
		p2p_continue_find(p2p);
	} else {
		p2p_dbg(p2p, "Running p2p_scan");
		p2p->p2p_scan_running = 1;
		eloop_cancel_timeout(p2p_scan_timeout, p2p, NULL);
		eloop_register_timeout(P2P_SCAN_TIMEOUT, 0, p2p_scan_timeout,
				       p2p, NULL);
	}
}