#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ distance; scalar_t__ state; scalar_t__ guid; int /*<<< orphan*/  heap_id; TYPE_4__* used_link; TYPE_4__* links; scalar_t__ hops; int /*<<< orphan*/  lid; } ;
typedef  TYPE_1__ vertex_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/  p_log; } ;
typedef  TYPE_2__ osm_ucast_mgr_t ;
struct TYPE_16__ {int /*<<< orphan*/ * p_node; TYPE_7__* p_physp; } ;
typedef  TYPE_3__ osm_port_t ;
typedef  int /*<<< orphan*/  osm_node_t ;
struct TYPE_17__ {scalar_t__ guid; int weight; size_t to; size_t from; struct TYPE_17__* next; int /*<<< orphan*/  to_port; int /*<<< orphan*/  from_port; } ;
typedef  TYPE_4__ link_t ;
typedef  int /*<<< orphan*/  binary_heap_t ;
struct TYPE_18__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 scalar_t__ DISCOVERED ; 
 scalar_t__ IB_NODE_TYPE_CA ; 
 scalar_t__ IB_NODE_TYPE_SWITCH ; 
 scalar_t__ INF ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 scalar_t__ UNDISCOVERED ; 
 void* cl_ntoh64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int heap_create (TYPE_1__*,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* heap_getmin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_heapify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ osm_link_is_healthy (TYPE_7__*) ; 
 int /*<<< orphan*/  osm_node_get_node_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * osm_node_get_remote_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ osm_node_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_default_link (TYPE_4__*) ; 
 int /*<<< orphan*/  set_default_vertex (TYPE_1__*) ; 

__attribute__((used)) static int dijkstra(osm_ucast_mgr_t * p_mgr, vertex_t * adj_list,
		    uint32_t adj_list_size, osm_port_t * port, uint16_t lid)
{
	uint32_t i = 0, j = 0, index = 0;
	osm_node_t *remote_node = NULL;
	uint8_t remote_port = 0;
	vertex_t *current = NULL;
	link_t *link = NULL;
	uint64_t guid = 0;
	binary_heap_t *heap = NULL;
	int err = 0;

	OSM_LOG_ENTER(p_mgr->p_log);

	/* reset all switches for new round with a new source for dijkstra */
	for (i = 1; i < adj_list_size; i++) {
		adj_list[i].hops = 0;
		adj_list[i].used_link = NULL;
		adj_list[i].distance = INF;
		adj_list[i].state = UNDISCOVERED;
	}

	/* if behind port is a Hca -> set adj_list[0] */
	if (osm_node_get_type(port->p_node) == IB_NODE_TYPE_CA) {
		/* save old link to prevent many mallocs after set_default_... */
		link = adj_list[0].links;
		/* initialize adj_list[0] (the source for the routing, a Hca) */
		set_default_vertex(&adj_list[0]);
		adj_list[0].guid =
		    cl_ntoh64(osm_node_get_node_guid(port->p_node));
		adj_list[0].lid = lid;
		index = 0;
		/* write saved link back to new adj_list[0] */
		adj_list[0].links = link;

		/* initialize link to neighbor for adj_list[0];
		   make sure the link is healthy
		 */
		if (port->p_physp && osm_link_is_healthy(port->p_physp)) {
			remote_node =
			    osm_node_get_remote_node(port->p_node,
						     port->p_physp->port_num,
						     &remote_port);
			/* if there is no remote node on this port or it's the same Hca -> ignore */
			if (remote_node
			    && (osm_node_get_type(remote_node) ==
				IB_NODE_TYPE_SWITCH)) {
				if (!(adj_list[0].links)) {
					adj_list[0].links =
					    (link_t *) malloc(sizeof(link_t));
					if (!(adj_list[0].links)) {
						OSM_LOG(p_mgr->p_log,
							OSM_LOG_ERROR,
							"ERR AD07: cannot allocate memory for a link\n");
						return 1;
					}
				}
				set_default_link(adj_list[0].links);
				adj_list[0].links->guid =
				    cl_ntoh64(osm_node_get_node_guid
					      (remote_node));
				adj_list[0].links->from_port =
				    port->p_physp->port_num;
				adj_list[0].links->to_port = remote_port;
				adj_list[0].links->weight = 1;
				for (j = 1; j < adj_list_size; j++) {
					if (adj_list[0].links->guid ==
					    adj_list[j].guid) {
						adj_list[0].links->to = j;
						break;
					}
				}
			}
		} else {
			/* if link is unhealthy then there's a severe issue */
			OSM_LOG(p_mgr->p_log, OSM_LOG_ERROR,
				"ERR AD0B: unsupported network state (CA with"
				" unhealthy link state discovered; should have"
				" been filtered out before already; gracefully"
				" shutdown this routing engine)\n");
			return 1;
		}
		/* if behind port is a switch -> search switch in adj_list */
	} else {
		/* reset adj_list[0], if links=NULL reset was done before, then skip */
		if (adj_list[0].links) {
			free(adj_list[0].links);
			set_default_vertex(&adj_list[0]);
		}
		/* search for the switch which is the source in this round */
		guid = cl_ntoh64(osm_node_get_node_guid(port->p_node));
		for (i = 1; i < adj_list_size; i++) {
			if (guid == adj_list[i].guid) {
				index = i;
				break;
			}
		}
	}

	/* source in dijkstra */
	adj_list[index].distance = 0;
	adj_list[index].state = DISCOVERED;
	adj_list[index].hops = 0;	/* the source has hop count = 0 */

	/* create a heap to find (efficient) the node with the smallest distance */
	if (osm_node_get_type(port->p_node) == IB_NODE_TYPE_CA)
		err = heap_create(adj_list, adj_list_size, &heap);
	else
		err = heap_create(&adj_list[1], adj_list_size - 1, &heap);
	if (err) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_ERROR,
			"ERR AD09: cannot allocate memory for heap or heap->node in heap_create(...)\n");
		return err;
	}

	current = heap_getmin(heap);
	while (current) {
		current->state = DISCOVERED;
		if (current->used_link)	/* increment the number of hops to the source for each new node */
			current->hops =
			    adj_list[current->used_link->from].hops + 1;

		/* add/update nodes which aren't discovered but accessible */
		for (link = current->links; link != NULL; link = link->next) {
			if ((adj_list[link->to].state != DISCOVERED)
			    && (current->distance + link->weight <
				adj_list[link->to].distance)) {
				adj_list[link->to].used_link = link;
				adj_list[link->to].distance =
				    current->distance + link->weight;
				heap_heapify(heap, adj_list[link->to].heap_id);
			}
		}

		current = heap_getmin(heap);
	}

	/* destroy the heap */
	heap_free(heap);
	heap = NULL;

	OSM_LOG_EXIT(p_mgr->p_log);
	return 0;
}