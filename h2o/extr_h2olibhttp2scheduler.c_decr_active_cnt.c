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
struct TYPE_5__ {TYPE_3__* _parent; } ;
struct TYPE_6__ {scalar_t__ _active_cnt; TYPE_1__ node; int /*<<< orphan*/  _queue_node; } ;
typedef  TYPE_2__ h2o_http2_scheduler_openref_t ;
struct TYPE_7__ {int /*<<< orphan*/ * _parent; } ;
typedef  TYPE_3__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_unset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decr_active_cnt(h2o_http2_scheduler_node_t *node)
{
    h2o_http2_scheduler_openref_t *ref;

    /* do nothing if node is the root */
    if (node->_parent == NULL)
        return;

    ref = (h2o_http2_scheduler_openref_t *)node;
    if (--ref->_active_cnt != 0)
        return;
    /* just changed to inactive */
    queue_unset(&ref->_queue_node);
    /* delegate the change towards root */
    decr_active_cnt(ref->node._parent);
}