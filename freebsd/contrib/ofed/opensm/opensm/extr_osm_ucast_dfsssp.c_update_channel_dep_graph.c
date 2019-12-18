#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_22__ {TYPE_1__* p_physp; TYPE_4__* p_node; } ;
typedef  TYPE_3__ osm_port_t ;
struct TYPE_23__ {TYPE_2__* sw; } ;
typedef  TYPE_4__ osm_node_t ;
struct TYPE_24__ {int channelID; struct TYPE_24__* linklist; struct TYPE_24__* srcdest_pairs; struct TYPE_24__* next; scalar_t__ num_pairs; struct TYPE_24__* node; } ;
typedef  TYPE_5__ cdg_node_t ;
typedef  TYPE_5__ cdg_link_t ;
struct TYPE_21__ {scalar_t__* new_lft; } ;
struct TYPE_20__ {scalar_t__ port_num; } ;

/* Variables and functions */
 scalar_t__ OSM_NO_PATH ; 
 int /*<<< orphan*/  cdg_insert (TYPE_5__**,TYPE_5__*) ; 
 TYPE_5__* cdg_search (TYPE_5__*,int) ; 
 size_t cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  osm_node_get_base_lid (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* osm_node_get_remote_node (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  set_default_cdg_node (TYPE_5__*) ; 
 int /*<<< orphan*/  set_next_srcdest_pair (TYPE_5__*,int) ; 

__attribute__((used)) static int update_channel_dep_graph(cdg_node_t ** cdg_root,
				    osm_port_t * src_port, uint16_t slid,
				    osm_port_t * dest_port, uint16_t dlid)
{
	osm_node_t *local_node = NULL, *remote_node = NULL;
	uint16_t local_lid = 0, remote_lid = 0;
	uint32_t srcdest = 0;
	uint8_t local_port = 0, remote_port = 0;
	uint64_t channelID = 0;

	cdg_node_t *channel_head = NULL, *channel = NULL, *last_channel = NULL;
	cdg_link_t *linklist = NULL;

	/* set the identifier for the src/dest pair to save this on each edge of the cdg */
	srcdest = (((uint32_t) slid) << 16) + ((uint32_t) dlid);

	channel_head = (cdg_node_t *) malloc(sizeof(cdg_node_t));
	if (!channel_head)
		goto ERROR;
	set_default_cdg_node(channel_head);
	last_channel = channel_head;

	/* if src is a Hca, then the channel from Hca to switch would be a source in the graph
	   sources can't be part of a cycle -> skip this channel
	 */
	remote_node =
	    osm_node_get_remote_node(src_port->p_node,
				     src_port->p_physp->port_num, &remote_port);

	while (remote_node && remote_node->sw) {
		local_node = remote_node;
		local_port = local_node->sw->new_lft[dlid];
		/* sanity check: local_port must be set or routing is broken */
		if (local_port == OSM_NO_PATH)
			goto ERROR;
		local_lid = cl_ntoh16(osm_node_get_base_lid(local_node, 0));
		/* each port belonging to a switch has lmc==0 -> get_base_lid is fine
		   (local/remote port in this function are always part of a switch)
		 */

		remote_node =
		    osm_node_get_remote_node(local_node, local_port,
					     &remote_port);
		/* if remote_node is a Hca, then the last channel from switch to Hca would be a sink in the cdg -> skip */
		if (!remote_node || !remote_node->sw)
			break;
		remote_lid = cl_ntoh16(osm_node_get_base_lid(remote_node, 0));

		channelID =
		    (((uint64_t) local_lid) << 48) +
		    (((uint64_t) local_port) << 32) +
		    (((uint64_t) remote_lid) << 16) + ((uint64_t) remote_port);
		channel = cdg_search(*cdg_root, channelID);
		if (channel) {
			/* check whether last channel has connection to this channel, i.e. subpath already exists in cdg */
			linklist = last_channel->linklist;
			while (linklist && linklist->node != channel
			       && linklist->next)
				linklist = linklist->next;
			/* if there is no connection, add one */
			if (linklist) {
				if (linklist->node == channel) {
					set_next_srcdest_pair(linklist,
							      srcdest);
				} else {
					linklist->next =
					    (cdg_link_t *)
					    malloc(sizeof(cdg_link_t));
					if (!linklist->next)
						goto ERROR;
					linklist = linklist->next;
					linklist->node = channel;
					linklist->num_pairs = 0;
					linklist->srcdest_pairs = NULL;
					set_next_srcdest_pair(linklist,
							      srcdest);
					linklist->next = NULL;
				}
			} else {
				/* either this is the first channel of the path, or the last channel was a new channel, or last channel was a sink */
				last_channel->linklist =
				    (cdg_link_t *) malloc(sizeof(cdg_link_t));
				if (!last_channel->linklist)
					goto ERROR;
				last_channel->linklist->node = channel;
				last_channel->linklist->num_pairs = 0;
				last_channel->linklist->srcdest_pairs = NULL;
				set_next_srcdest_pair(last_channel->linklist,
						      srcdest);
				last_channel->linklist->next = NULL;
			}
		} else {
			/* create new channel */
			channel = (cdg_node_t *) malloc(sizeof(cdg_node_t));
			if (!channel)
				goto ERROR;
			set_default_cdg_node(channel);
			channel->channelID = channelID;
			cdg_insert(cdg_root, channel);

			/* go to end of link list of last channel */
			linklist = last_channel->linklist;
			while (linklist && linklist->next)
				linklist = linklist->next;
			if (linklist) {
				/* update last link of an existing channel */
				linklist->next =
				    (cdg_link_t *) malloc(sizeof(cdg_link_t));
				if (!linklist->next)
					goto ERROR;
				linklist = linklist->next;
				linklist->node = channel;
				linklist->num_pairs = 0;
				linklist->srcdest_pairs = NULL;
				set_next_srcdest_pair(linklist, srcdest);
				linklist->next = NULL;
			} else {
				/* either this is the first channel of the path, or the last channel was a new channel, or last channel was a sink */
				last_channel->linklist =
				    (cdg_link_t *) malloc(sizeof(cdg_link_t));
				if (!last_channel->linklist)
					goto ERROR;
				last_channel->linklist->node = channel;
				last_channel->linklist->num_pairs = 0;
				last_channel->linklist->srcdest_pairs = NULL;
				set_next_srcdest_pair(last_channel->linklist,
						      srcdest);
				last_channel->linklist->next = NULL;
			}
		}
		last_channel = channel;
	}

	if (channel_head->linklist) {
		if (channel_head->linklist->srcdest_pairs)
			free(channel_head->linklist->srcdest_pairs);
		free(channel_head->linklist);
	}
	free(channel_head);

	return 0;

ERROR:
	/* cleanup data and exit */
	if (channel_head) {
		if (channel_head->linklist)
			free(channel_head->linklist);
		free(channel_head);
	}

	return 1;
}