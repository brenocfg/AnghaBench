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
struct TYPE_3__ {scalar_t__ bits; int /*<<< orphan*/  anchor257; } ;
typedef  TYPE_1__ h2o_http2_scheduler_queue_t ;

/* Variables and functions */
 scalar_t__ h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_is_empty(h2o_http2_scheduler_queue_t *queue)
{
    return queue->bits == 0 && h2o_linklist_is_empty(&queue->anchor257);
}