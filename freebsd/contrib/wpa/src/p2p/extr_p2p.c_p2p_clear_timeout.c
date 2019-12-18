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
struct p2p_data {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_state_timeout ; 
 int /*<<< orphan*/  p2p_state_txt (int /*<<< orphan*/ ) ; 

void p2p_clear_timeout(struct p2p_data *p2p)
{
	p2p_dbg(p2p, "Clear timeout (state=%s)", p2p_state_txt(p2p->state));
	eloop_cancel_timeout(p2p_state_timeout, p2p, NULL);
}