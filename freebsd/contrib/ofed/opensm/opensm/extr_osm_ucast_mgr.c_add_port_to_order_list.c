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
struct TYPE_7__ {int /*<<< orphan*/  port_order_list; TYPE_2__* p_subn; } ;
typedef  TYPE_3__ osm_ucast_mgr_t ;
struct TYPE_8__ {scalar_t__ flag; int /*<<< orphan*/  list_item; int /*<<< orphan*/  use_scatter; } ;
typedef  TYPE_4__ osm_port_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  scatter_ports; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_port_to_order_list(cl_map_item_t * p_map_item, void *ctx)
{
	osm_port_t *port = (osm_port_t *) p_map_item;
	osm_ucast_mgr_t *m = ctx;

	if (!port->flag) {
		port->use_scatter = m->p_subn->opt.scatter_ports;
		cl_qlist_insert_tail(&m->port_order_list, &port->list_item);
	} else
		port->flag = 0;
}