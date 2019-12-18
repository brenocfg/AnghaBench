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
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int p2p_intra_bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,char*) ; 

void p2p_set_intra_bss_dist(struct p2p_data *p2p, int enabled)
{
	p2p_dbg(p2p, "Intra BSS distribution %s",
		enabled ? "enabled" : "disabled");
	p2p->cfg->p2p_intra_bss = enabled;
}