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
struct TYPE_3__ {int /*<<< orphan*/  _link; } ;
typedef  TYPE_1__ h2o_http2_scheduler_queue_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_unset(h2o_http2_scheduler_queue_node_t *node)
{
    assert(h2o_linklist_is_linked(&node->_link));
    h2o_linklist_unlink(&node->_link);
}