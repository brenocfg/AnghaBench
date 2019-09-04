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
struct TYPE_3__ {int /*<<< orphan*/ * _queue; } ;
typedef  TYPE_1__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_is_empty (int /*<<< orphan*/ *) ; 

int h2o_http2_scheduler_is_active(h2o_http2_scheduler_node_t *root)
{
    return root->_queue != NULL && !queue_is_empty(root->_queue);
}