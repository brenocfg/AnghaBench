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
struct torus {TYPE_4__* osm; } ;
struct t_switch {TYPE_2__** port; } ;
struct TYPE_7__ {unsigned int min_sw_data_vls; unsigned int min_data_vls; } ;
struct TYPE_8__ {TYPE_3__ subn; } ;
struct TYPE_6__ {TYPE_1__* pgrp; } ;
struct TYPE_5__ {int port_grp; } ;

/* Variables and functions */
 unsigned int TORUS_MAX_DIM ; 
 int /*<<< orphan*/  sl_get_qos (unsigned int) ; 
 int /*<<< orphan*/  sl_get_use_loop_vl (unsigned int,unsigned int) ; 
 unsigned int vl_set_ca_qos_vl (int /*<<< orphan*/ ) ; 
 unsigned int vl_set_loop_vl (int /*<<< orphan*/ ) ; 
 unsigned int vl_set_qos_vl (int /*<<< orphan*/ ) ; 
 unsigned int vl_set_turn_vl (unsigned int,unsigned int) ; 

__attribute__((used)) static
unsigned sl2vl_entry(struct torus *t, struct t_switch *sw,
		     int input_pt, int output_pt, unsigned sl)
{
	unsigned id, od, vl, data_vls;

	if (sw && sw->port[input_pt])
		id = sw->port[input_pt]->pgrp->port_grp / 2;
	else
		id = TORUS_MAX_DIM;

	if (sw && sw->port[output_pt])
		od = sw->port[output_pt]->pgrp->port_grp / 2;
	else
		od = TORUS_MAX_DIM;

	if (sw)
		data_vls = t->osm->subn.min_sw_data_vls;
	else
		data_vls = t->osm->subn.min_data_vls;

	vl = 0;
	if (sw && od != TORUS_MAX_DIM) {
		if (data_vls >= 2)
			vl |= vl_set_loop_vl(sl_get_use_loop_vl(sl, od));
		if (data_vls >= 4)
			vl |= vl_set_turn_vl(id, od);
		if (data_vls >= 8)
			vl |= vl_set_qos_vl(sl_get_qos(sl));
	} else {
		if (data_vls >= 2)
			vl |= vl_set_ca_qos_vl(sl_get_qos(sl));
	}
	return vl;
}