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
struct torus {struct t_switch**** sw; } ;
struct t_switch {size_t i; size_t j; size_t k; } ;

/* Variables and functions */
 int ring_dir_path (struct torus*,unsigned int,struct t_switch*,struct t_switch*) ; 

__attribute__((used)) static
bool next_hop_path(struct torus *t, unsigned cdir,
		   struct t_switch *ssw, struct t_switch *dsw,
		   unsigned *pt_grp)
{
	struct t_switch *tsw = NULL;
	bool success = false;
	int d;

	/*
	 * If the path from ssw to dsw turns, this is the switch where the
	 * turn happens.
	 */
	switch (cdir) {
	case 0:
		tsw = t->sw[dsw->i][ssw->j][ssw->k];
		break;
	case 1:
		tsw = t->sw[ssw->i][dsw->j][ssw->k];
		break;
	case 2:
		tsw = t->sw[ssw->i][ssw->j][dsw->k];
		break;
	default:
		goto out;
	}
	if (tsw) {
		d = ring_dir_path(t, cdir, ssw, tsw);
		cdir *= 2;
		if (d > 0)
			*pt_grp = cdir + 1;
		else if (d < 0)
			*pt_grp = cdir;
		else
			goto out;
		success = true;
	}
out:
	return success;
}