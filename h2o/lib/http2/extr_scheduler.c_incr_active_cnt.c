#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* _parent; } ;
struct TYPE_7__ {int _active_cnt; TYPE_1__ node; int /*<<< orphan*/  weight; int /*<<< orphan*/  _queue_node; } ;
typedef  TYPE_2__ h2o_http2_scheduler_openref_t ;
struct TYPE_8__ {int /*<<< orphan*/ * _parent; } ;
typedef  TYPE_3__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  queue_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void incr_active_cnt(h2o_http2_scheduler_node_t *node)
{
    h2o_http2_scheduler_openref_t *ref;

    /* do nothing if node is the root */
    if (node->_parent == NULL)
        return;

    ref = (h2o_http2_scheduler_openref_t *)node;
    if (++ref->_active_cnt != 1)
        return;
    /* just changed to active */
    queue_set(get_queue(ref->node._parent), &ref->_queue_node, ref->weight);
    /* delegate the change towards root */
    incr_active_cnt(ref->node._parent);
}