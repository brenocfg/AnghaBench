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
struct link {struct endpoint* end; } ;
struct f_switch {int port_cnt; scalar_t__ n_id; TYPE_1__** port; } ;
struct endpoint {scalar_t__ n_id; scalar_t__ type; struct f_switch* sw; } ;
struct TYPE_2__ {scalar_t__ type; struct link* link; scalar_t__ sw; } ;

/* Variables and functions */
 scalar_t__ PASSTHRU ; 
 scalar_t__ ffind_face_corner (struct f_switch*,struct f_switch*,struct f_switch*) ; 

struct f_switch *ffind_3d_perpendicular(struct f_switch *fsw0,
					struct f_switch *fsw1,
					struct f_switch *fsw2,
					struct f_switch *fsw3)
{
	int p1;
	struct link *l;
	struct endpoint *far_end;
	struct f_switch *fsw4 = NULL;

	if (!(fsw0 && fsw1 && fsw2 && fsw3))
		goto out;

	/*
	 * Look at all the ports on the switch, fsw1,  that is the base of
	 * the perpendicular.
	 */
	for (p1 = 0; p1 < fsw1->port_cnt; p1++) {
		/*
		 * Ignore everything except switch links that haven't
		 * been installed into the torus.
		 */
		if (!(fsw1->port[p1] && fsw1->port[p1]->sw &&
		      fsw1->port[p1]->type == PASSTHRU))
			continue;

		l = fsw1->port[p1]->link;

		if (l->end[0].n_id == fsw1->n_id)
			far_end = &l->end[1];
		else
			far_end = &l->end[0];
		/*
		 * Ignore CAs
		 */
		if (!(far_end->type == PASSTHRU && far_end->sw))
			continue;

		fsw4 = far_end->sw;
		if (fsw4->n_id == fsw3->n_id)	/* wrong perpendicular */
			continue;

		if (ffind_face_corner(fsw0, fsw1, fsw4) &&
		    ffind_face_corner(fsw2, fsw1, fsw4))
			goto out;
	}
	fsw4 = NULL;
out:
	return fsw4;
}