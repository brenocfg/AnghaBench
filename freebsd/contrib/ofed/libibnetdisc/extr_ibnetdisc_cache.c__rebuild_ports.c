#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* remoteport; int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ ibnd_port_t ;
struct TYPE_14__ {TYPE_2__* port; int /*<<< orphan*/  remoteport_cache_key; scalar_t__ remoteport_flag; int /*<<< orphan*/  node_guid; struct TYPE_14__* next; } ;
typedef  TYPE_3__ ibnd_port_cache_t ;
struct TYPE_15__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_4__ ibnd_node_cache_t ;
struct TYPE_16__ {TYPE_1__* f_int; TYPE_3__* ports_cache; } ;
typedef  TYPE_5__ ibnd_fabric_cache_t ;
struct TYPE_12__ {int /*<<< orphan*/  lid2guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*) ; 
 TYPE_4__* _find_node (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* _find_port (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_to_portlid_hash (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rebuild_ports(ibnd_fabric_cache_t * fabric_cache)
{
	ibnd_port_cache_t *port_cache;
	ibnd_port_cache_t *port_cache_next;

	port_cache = fabric_cache->ports_cache;
	while (port_cache) {
		ibnd_node_cache_t *node_cache;
		ibnd_port_cache_t *remoteport_cache;
		ibnd_port_t *port;

		port_cache_next = port_cache->next;

		port = port_cache->port;

		if (!(node_cache =
		      _find_node(fabric_cache, port_cache->node_guid))) {
			IBND_DEBUG("Cache invalid: cannot find node\n");
			return -1;
		}

		port->node = node_cache->node;

		if (port_cache->remoteport_flag) {
			if (!(remoteport_cache = _find_port(fabric_cache,
							    &port_cache->remoteport_cache_key)))
			{
				IBND_DEBUG
				    ("Cache invalid: cannot find remote port\n");
				return -1;
			}

			port->remoteport = remoteport_cache->port;
		} else
			port->remoteport = NULL;

		add_to_portlid_hash(port, fabric_cache->f_int->lid2guid);
		port_cache = port_cache_next;
	}

	return 0;
}