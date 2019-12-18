#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* p_subn; } ;
typedef  TYPE_2__ osm_ucast_mgr_t ;
struct TYPE_7__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_3__ osm_port_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  port_guid_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_ports_priv(osm_ucast_mgr_t * mgr)
{
	cl_qmap_t *port_tbl = &mgr->p_subn->port_guid_tbl;
	osm_port_t *port;
	cl_map_item_t *item;
	for (item = cl_qmap_head(port_tbl); item != cl_qmap_end(port_tbl);
	     item = cl_qmap_next(item)) {
		port = (osm_port_t *) item;
		if (port->priv) {
			free(port->priv);
			port->priv = NULL;
		}
	}
}