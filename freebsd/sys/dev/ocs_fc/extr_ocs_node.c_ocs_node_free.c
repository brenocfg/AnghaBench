#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/ * current_state; } ;
struct TYPE_22__ {int /*<<< orphan*/  fc_id; } ;
struct TYPE_23__ {int /*<<< orphan*/  nodes_free_list; int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  pend_frames_lock; TYPE_7__ sm; struct TYPE_23__* sport; int /*<<< orphan*/  node_list; TYPE_16__ rnode; int /*<<< orphan*/ * lookup; struct TYPE_23__* ocs; scalar_t__ fcp2device; int /*<<< orphan*/  gidpt_delay_timer; int /*<<< orphan*/  hw; scalar_t__ refound; struct TYPE_23__* xport; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  TYPE_1__ ocs_t ;
typedef  TYPE_1__ ocs_sport_t ;
typedef  TYPE_1__ ocs_node_t ;
typedef  int ocs_hw_rtn_e ;
typedef  int int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FC_ADDR_NAMESERVER ; 
 int /*<<< orphan*/  OCS_EVT_ALL_CHILD_NODES_FREE ; 
 int /*<<< orphan*/  OCS_EVT_RSCN_RCVD ; 
 scalar_t__ OCS_HW_RTN_IS_ERROR (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  node_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_del_crn (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_device_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_device_unlock (TYPE_1__*) ; 
 int ocs_hw_node_free_resources (int /*<<< orphan*/ *,TYPE_16__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,...) ; 
 TYPE_1__* ocs_node_find (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_node_lock_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_node_post_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sm_post_event (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sport_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_sport_unlock (TYPE_1__*) ; 
 scalar_t__ ocs_timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t
ocs_node_free(ocs_node_t *node)
{
	ocs_sport_t *sport;
	ocs_t *ocs;
	ocs_xport_t *xport;
	ocs_hw_rtn_e rc = 0;
	ocs_node_t *ns = NULL;
	int post_all_free = FALSE;

	ocs_assert(node, -1);
	ocs_assert(node->sport, -1);
	ocs_assert(node->ocs, -1);
	sport = node->sport;
	ocs_assert(sport, -1);
	ocs = node->ocs;
	ocs_assert(ocs->xport, -1);
	xport = ocs->xport;

	node_printf(node, "Free'd\n");

	if(node->refound) {
		/*
		 * Save the name server node. We will send fake RSCN event at
		 * the end to handle ignored RSCN event during node deletion
		 */
		ns = ocs_node_find(node->sport, FC_ADDR_NAMESERVER);
	}

	/* Remove from node list */
	ocs_sport_lock(sport);
		ocs_list_remove(&sport->node_list, node);

		/* Free HW resources */
		if (OCS_HW_RTN_IS_ERROR((rc = ocs_hw_node_free_resources(&ocs->hw, &node->rnode)))) {
			ocs_log_test(ocs, "ocs_hw_node_free failed: %d\n", rc);
			rc = -1;
		}

		/* if the gidpt_delay_timer is still running, then delete it */
		if (ocs_timer_pending(&node->gidpt_delay_timer)) {
			ocs_del_timer(&node->gidpt_delay_timer);
		}

		if (node->fcp2device) {
			ocs_del_crn(node);
		}

		/* remove entry from sparse vector list */
		if (sport->lookup == NULL) {
			ocs_log_test(node->ocs, "assertion failed: sport lookup is NULL\n");
			ocs_sport_unlock(sport);
			return -1;
		}

		spv_set(sport->lookup, node->rnode.fc_id, NULL);

		/*
		 * If the node_list is empty, then post a ALL_CHILD_NODES_FREE event to the sport,
		 * after the lock is released.  The sport may be free'd as a result of the event.
		 */
		if (ocs_list_empty(&sport->node_list)) {
			post_all_free = TRUE;
		}

	ocs_sport_unlock(sport);

	if (post_all_free) {
		ocs_sm_post_event(&sport->sm, OCS_EVT_ALL_CHILD_NODES_FREE, NULL);
	}

	node->sport = NULL;
	node->sm.current_state = NULL;

	ocs_node_lock_free(node);
	ocs_lock_free(&node->pend_frames_lock);
	ocs_lock_free(&node->active_ios_lock);

	/* return to free list */
	ocs_device_lock(ocs);
		ocs_list_add_tail(&xport->nodes_free_list, node);
	ocs_device_unlock(ocs);

	if(ns != NULL) {
		/* sending fake RSCN event to name server node */
		ocs_node_post_event(ns, OCS_EVT_RSCN_RCVD, NULL);
	}

	return rc;
}