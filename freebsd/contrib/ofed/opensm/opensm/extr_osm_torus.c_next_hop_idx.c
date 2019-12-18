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
struct torus {int /*<<< orphan*/  z_sz; int /*<<< orphan*/  y_sz; int /*<<< orphan*/  x_sz; } ;
struct t_switch {TYPE_1__* ptgrp; int /*<<< orphan*/  k; int /*<<< orphan*/  j; int /*<<< orphan*/  i; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_cnt; } ;

/* Variables and functions */
 int ring_dir_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool next_hop_idx(struct torus *t, unsigned cdir,
		  struct t_switch *ssw, struct t_switch *dsw,
		  unsigned *pt_grp)
{
	int d;
	unsigned g;
	bool success = false;

	switch (cdir) {
	case 0:
		d = ring_dir_idx(ssw->i, dsw->i, t->x_sz);
		break;
	case 1:
		d = ring_dir_idx(ssw->j, dsw->j, t->y_sz);
		break;
	case 2:
		d = ring_dir_idx(ssw->k, dsw->k, t->z_sz);
		break;
	default:
		goto out;
	}

	cdir *= 2;
	if (d > 0)
		g = cdir + 1;
	else if (d < 0)
		g = cdir;
	else
		goto out;

	if (!ssw->ptgrp[g].port_cnt)
		goto out;

	*pt_grp = g;
	success = true;
out:
	return success;
}