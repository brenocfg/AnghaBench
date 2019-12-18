#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* p_osm; } ;
typedef  TYPE_4__ updn_t ;
struct updn_node {scalar_t__ rank; } ;
struct TYPE_14__ {unsigned int num_hops; int /*<<< orphan*/  num_ports; scalar_t__* hops; } ;
typedef  TYPE_5__ osm_switch_t ;
struct TYPE_15__ {TYPE_3__* p_node; } ;
typedef  TYPE_6__ osm_port_t ;
struct TYPE_12__ {TYPE_2__* sw; } ;
struct TYPE_11__ {scalar_t__ priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  subn; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* osm_get_port_by_lid_ho (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void updn_clear_non_root_hops(updn_t * updn, osm_switch_t * sw)
{
	osm_port_t *port;
	unsigned i;

	for (i = 0; i < sw->num_hops; i++)
		if (sw->hops[i]) {
			port = osm_get_port_by_lid_ho(&updn->p_osm->subn, i);
			if (!port || !port->p_node->sw
			    || ((struct updn_node *)port->p_node->sw->priv)->
			    rank != 0)
				memset(sw->hops[i], 0xff, sw->num_ports);
		}
}