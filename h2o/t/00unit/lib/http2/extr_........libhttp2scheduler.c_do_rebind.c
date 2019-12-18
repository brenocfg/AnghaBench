#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* _parent; } ;
struct TYPE_12__ {scalar_t__ _active_cnt; TYPE_1__ node; int /*<<< orphan*/  weight; int /*<<< orphan*/  _queue_node; int /*<<< orphan*/  _all_link; } ;
typedef  TYPE_2__ h2o_http2_scheduler_openref_t ;
struct TYPE_13__ {int /*<<< orphan*/  _all_refs; } ;
typedef  TYPE_3__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  convert_to_exclusive (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decr_active_cnt (TYPE_3__*) ; 
 int /*<<< orphan*/  get_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incr_active_cnt (TYPE_3__*) ; 
 int /*<<< orphan*/  queue_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_unset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_rebind(h2o_http2_scheduler_openref_t *ref, h2o_http2_scheduler_node_t *new_parent, int exclusive)
{
    /* rebind _all_link */
    h2o_linklist_unlink(&ref->_all_link);
    h2o_linklist_insert(&new_parent->_all_refs, &ref->_all_link);
    /* rebind to WRR (as well as adjust active_cnt) */
    if (ref->_active_cnt != 0) {
        queue_unset(&ref->_queue_node);
        queue_set(get_queue(new_parent), &ref->_queue_node, ref->weight);
        decr_active_cnt(ref->node._parent);
        incr_active_cnt(new_parent);
    }
    /* update the backlinks */
    ref->node._parent = new_parent;

    if (exclusive)
        convert_to_exclusive(new_parent, ref);
}