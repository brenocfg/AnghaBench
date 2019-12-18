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
struct p2p_data {int /*<<< orphan*/ * go_neg_peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_IDLE ; 
 int /*<<< orphan*/  p2p_clear_timeout (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_clear_go_neg(struct p2p_data *p2p)
{
	p2p->go_neg_peer = NULL;
	p2p_clear_timeout(p2p);
	p2p_set_state(p2p, P2P_IDLE);
}