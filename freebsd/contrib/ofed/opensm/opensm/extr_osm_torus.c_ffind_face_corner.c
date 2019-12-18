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

__attribute__((used)) static
struct f_switch *ffind_face_corner(struct f_switch *fsw0,
				   struct f_switch *fsw1,
				   struct f_switch *fsw2)
{
	int p0, p3;
	struct link *l;
	struct endpoint *far_end;
	struct f_switch *fsw, *fsw3 = NULL;

	if (!(fsw0 && fsw1 && fsw2))
		goto out;

	for (p0 = 0; p0 < fsw0->port_cnt; p0++) {
		/*
		 * Ignore everything except switch links that haven't
		 * been installed into the torus.
		 */
		if (!(fsw0->port[p0] && fsw0->port[p0]->sw &&
		      fsw0->port[p0]->type == PASSTHRU))
			continue;

		l = fsw0->port[p0]->link;

		if (l->end[0].n_id == fsw0->n_id)
			far_end = &l->end[1];
		else
			far_end = &l->end[0];

		/*
		 * Ignore CAs
		 */
		if (!(far_end->type == PASSTHRU && far_end->sw))
			continue;

		fsw3 = far_end->sw;
		if (fsw3->n_id == fsw1->n_id)	/* existing corner */
			continue;

		for (p3 = 0; p3 < fsw3->port_cnt; p3++) {
			/*
			 * Ignore everything except switch links that haven't
			 * been installed into the torus.
			 */
			if (!(fsw3->port[p3] && fsw3->port[p3]->sw &&
			      fsw3->port[p3]->type == PASSTHRU))
				continue;

			l = fsw3->port[p3]->link;

			if (l->end[0].n_id == fsw3->n_id)
				far_end = &l->end[1];
			else
				far_end = &l->end[0];

			/*
			 * Ignore CAs
			 */
			if (!(far_end->type == PASSTHRU && far_end->sw))
				continue;

			fsw = far_end->sw;
			if (fsw->n_id == fsw2->n_id)
				goto out;
		}
	}
	fsw3 = NULL;
out:
	return fsw3;
}