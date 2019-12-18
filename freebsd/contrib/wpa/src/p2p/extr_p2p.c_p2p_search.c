#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct p2p_data {scalar_t__ find_type; int find_specified_freq; int /*<<< orphan*/  find_dev_id; int /*<<< orphan*/  req_dev_types; int /*<<< orphan*/  num_req_dev_types; TYPE_1__* cfg; scalar_t__ find_pending_full; scalar_t__ drv_in_listen; } ;
typedef  enum p2p_scan_type { ____Placeholder_p2p_scan_type } p2p_scan_type ;
struct TYPE_2__ {int (* p2p_scan ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* stop_listen ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 scalar_t__ P2P_FIND_PROGRESSIVE ; 
 scalar_t__ P2P_FIND_START_WITH_FULL ; 
 int P2P_SCAN_FULL ; 
 int P2P_SCAN_SOCIAL ; 
 int P2P_SCAN_SOCIAL_PLUS_ONE ; 
 int /*<<< orphan*/  p2p_continue_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int p2p_get_next_prog_freq (struct p2p_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_search(struct p2p_data *p2p)
{
	int freq = 0;
	enum p2p_scan_type type;
	u16 pw_id = DEV_PW_DEFAULT;
	int res;

	if (p2p->drv_in_listen) {
		p2p_dbg(p2p, "Driver is still in Listen state - wait for it to end before continuing");
		return;
	}
	p2p->cfg->stop_listen(p2p->cfg->cb_ctx);

	if (p2p->find_pending_full &&
	    (p2p->find_type == P2P_FIND_PROGRESSIVE ||
	     p2p->find_type == P2P_FIND_START_WITH_FULL)) {
		type = P2P_SCAN_FULL;
		p2p_dbg(p2p, "Starting search (pending full scan)");
		p2p->find_pending_full = 0;
	} else if ((p2p->find_type == P2P_FIND_PROGRESSIVE &&
	    (freq = p2p_get_next_prog_freq(p2p)) > 0) ||
	    (p2p->find_type == P2P_FIND_START_WITH_FULL &&
	     (freq = p2p->find_specified_freq) > 0)) {
		type = P2P_SCAN_SOCIAL_PLUS_ONE;
		p2p_dbg(p2p, "Starting search (+ freq %u)", freq);
	} else {
		type = P2P_SCAN_SOCIAL;
		p2p_dbg(p2p, "Starting search");
	}

	res = p2p->cfg->p2p_scan(p2p->cfg->cb_ctx, type, freq,
				 p2p->num_req_dev_types, p2p->req_dev_types,
				 p2p->find_dev_id, pw_id);
	if (res < 0) {
		p2p_dbg(p2p, "Scan request schedule failed");
		p2p_continue_find(p2p);
	}
}