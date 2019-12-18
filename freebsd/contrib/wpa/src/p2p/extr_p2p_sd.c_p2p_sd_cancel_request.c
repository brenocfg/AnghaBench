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
struct p2p_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,void*) ; 
 int /*<<< orphan*/  p2p_free_sd_query (void*) ; 
 scalar_t__ p2p_unlink_sd_query (struct p2p_data*,void*) ; 

int p2p_sd_cancel_request(struct p2p_data *p2p, void *req)
{
	if (p2p_unlink_sd_query(p2p, req)) {
		p2p_dbg(p2p, "Cancel pending SD query %p", req);
		p2p_free_sd_query(req);
		return 0;
	}
	return -1;
}