#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint32_t ;
struct TYPE_28__ {int /*<<< orphan*/  nodes_free_list; } ;
typedef  TYPE_2__ ocs_xport_t ;
struct TYPE_29__ {int /*<<< orphan*/  hw; TYPE_2__* xport; } ;
typedef  TYPE_3__ ocs_t ;
struct TYPE_30__ {int /*<<< orphan*/  lookup; int /*<<< orphan*/  node_list; scalar_t__ shutting_down; TYPE_3__* ocs; } ;
typedef  TYPE_4__ ocs_sport_t ;
struct TYPE_26__ {TYPE_5__* app; } ;
struct TYPE_27__ {TYPE_5__* node; int /*<<< orphan*/  indicator; } ;
struct TYPE_32__ {int size; TYPE_5__* virt; } ;
struct TYPE_31__ {int /*<<< orphan*/ * mgmt_functions; scalar_t__ evtdepth; TYPE_1__ sm; TYPE_21__ rnode; TYPE_6__ sparm_dma_buf; int /*<<< orphan*/  els_io_active_list; int /*<<< orphan*/  els_io_pend_list; int /*<<< orphan*/  active_ios; void* instance_index; int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  pend_frames; int /*<<< orphan*/  pend_frames_lock; void* targ; void* init; TYPE_3__* ocs; TYPE_4__* sport; void* max_wr_xfer_size; } ;
typedef  TYPE_5__ ocs_node_t ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  void* int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  node_mgmt_functions ; 
 int /*<<< orphan*/  ocs_assert (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_device_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_device_unlock (TYPE_3__*) ; 
 void* ocs_hw_node_alloc (int /*<<< orphan*/ *,TYPE_21__*,void*,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_hw_sequence_t ; 
 int /*<<< orphan*/  ocs_io_t ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock_init (TYPE_3__*,int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_3__*,char*,void*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_3__*,char*,void*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_node_lock_init (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_node_update_display_name (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_scsi_io_alloc_enable (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_sport_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_sport_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  spv_set (int /*<<< orphan*/ ,void*,TYPE_5__*) ; 

ocs_node_t *
ocs_node_alloc(ocs_sport_t *sport, uint32_t port_id, uint8_t init, uint8_t targ)
{
	int32_t rc;
	ocs_node_t *node = NULL;
	uint32_t instance_index;
	uint32_t max_wr_xfer_size;
	ocs_t *ocs = sport->ocs;
	ocs_xport_t *xport = ocs->xport;
	ocs_dma_t sparm_dma_buf;

	ocs_assert(sport, NULL);

	if (sport->shutting_down) {
		ocs_log_debug(ocs, "node allocation when shutting down %06x", port_id);
		return NULL;
	}

	ocs_device_lock(ocs);
		node = ocs_list_remove_head(&xport->nodes_free_list);
	ocs_device_unlock(ocs);
	if (node == NULL) {
		ocs_log_err(ocs, "node allocation failed %06x", port_id);
		return NULL;
	}

	/* Save persistent values across memset zero */
	instance_index = node->instance_index;
	max_wr_xfer_size = node->max_wr_xfer_size;
	sparm_dma_buf = node->sparm_dma_buf;

	ocs_memset(node, 0, sizeof(*node));
	node->instance_index = instance_index;
	node->max_wr_xfer_size = max_wr_xfer_size;
	node->sparm_dma_buf = sparm_dma_buf;
	node->rnode.indicator = UINT32_MAX;

	node->sport = sport;
	ocs_sport_lock(sport);

		node->ocs = ocs;
		node->init = init;
		node->targ = targ;

		rc = ocs_hw_node_alloc(&ocs->hw, &node->rnode, port_id, sport);
		if (rc) {
			ocs_log_err(ocs, "ocs_hw_node_alloc failed: %d\n", rc);
			ocs_sport_unlock(sport);

			/* Return back to pool. */
			ocs_device_lock(ocs);
			ocs_list_add_tail(&xport->nodes_free_list, node);
			ocs_device_unlock(ocs);

			return NULL;
		}
		ocs_list_add_tail(&sport->node_list, node);

		ocs_node_lock_init(node);
		ocs_lock_init(ocs, &node->pend_frames_lock, "pend_frames_lock[%d]", node->instance_index);
		ocs_list_init(&node->pend_frames, ocs_hw_sequence_t, link);
		ocs_lock_init(ocs, &node->active_ios_lock, "active_ios[%d]", node->instance_index);
		ocs_list_init(&node->active_ios, ocs_io_t, link);
		ocs_list_init(&node->els_io_pend_list, ocs_io_t, link);
		ocs_list_init(&node->els_io_active_list, ocs_io_t, link);
		ocs_scsi_io_alloc_enable(node);

		/* zero the service parameters */
		ocs_memset(node->sparm_dma_buf.virt, 0, node->sparm_dma_buf.size);

		node->rnode.node = node;
		node->sm.app = node;
		node->evtdepth = 0;

		ocs_node_update_display_name(node);

		spv_set(sport->lookup, port_id, node);
	ocs_sport_unlock(sport);
	node->mgmt_functions = &node_mgmt_functions;

	return node;
}