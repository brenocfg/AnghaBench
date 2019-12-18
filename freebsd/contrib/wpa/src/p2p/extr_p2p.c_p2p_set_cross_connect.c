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
struct p2p_data {int cross_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,char*) ; 

void p2p_set_cross_connect(struct p2p_data *p2p, int enabled)
{
	p2p_dbg(p2p, "Cross connection %s", enabled ? "enabled" : "disabled");
	if (p2p->cross_connect == enabled)
		return;
	p2p->cross_connect = enabled;
	/* TODO: may need to tear down any action group where we are GO(?) */
}