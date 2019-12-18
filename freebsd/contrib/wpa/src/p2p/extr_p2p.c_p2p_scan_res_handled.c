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
struct p2p_data {scalar_t__ state; scalar_t__ p2p_scan_running; } ;

/* Variables and functions */
 scalar_t__ P2P_SEARCH ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_continue_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 scalar_t__ p2p_run_after_scan (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_scan_timeout ; 

void p2p_scan_res_handled(struct p2p_data *p2p)
{
	if (!p2p->p2p_scan_running) {
		p2p_dbg(p2p, "p2p_scan was not running, but scan results received");
	}
	p2p->p2p_scan_running = 0;
	eloop_cancel_timeout(p2p_scan_timeout, p2p, NULL);

	if (p2p_run_after_scan(p2p))
		return;
	if (p2p->state == P2P_SEARCH)
		p2p_continue_find(p2p);
}