#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_http2_scheduler_queue_t ;
struct TYPE_3__ {int /*<<< orphan*/ * _queue; } ;
typedef  TYPE_1__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static h2o_http2_scheduler_queue_t *get_queue(h2o_http2_scheduler_node_t *node)
{
    if (node->_queue == NULL) {
        node->_queue = h2o_mem_alloc(sizeof(*node->_queue));
        queue_init(node->_queue);
    }
    return node->_queue;
}