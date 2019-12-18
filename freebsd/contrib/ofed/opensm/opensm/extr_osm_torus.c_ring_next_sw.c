#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct t_switch {TYPE_2__* ptgrp; } ;
struct TYPE_8__ {TYPE_3__* end; } ;
struct TYPE_7__ {struct t_switch* sw; } ;
struct TYPE_6__ {TYPE_1__** port; int /*<<< orphan*/  port_cnt; } ;
struct TYPE_5__ {TYPE_4__* link; } ;

/* Variables and functions */

__attribute__((used)) static
struct t_switch *ring_next_sw(struct t_switch *sw, unsigned cdir, int rdir)
{
	unsigned pt_grp, far_end = 0;

	if (!rdir)
		return NULL;
	/*
	 * Recall that links are installed into the torus so that their 1 end
	 * is in the "positive" coordinate direction relative to their 0 end
	 * (see link_tswitches() and connect_tlink()).  Recall also that for
	 * interswitch links, all links in a given switch port group have the
	 * same endpoints, so we just need to look at the first link.
	 */
	pt_grp = 2 * cdir;
	if (rdir > 0) {
		pt_grp++;
		far_end = 1;
	}

	if (!sw->ptgrp[pt_grp].port_cnt)
		return NULL;

	return sw->ptgrp[pt_grp].port[0]->link->end[far_end].sw;
}