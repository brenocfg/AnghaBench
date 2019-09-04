#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 TYPE_1__* finished_aio_queue ; 
 TYPE_1__* queue_del_first_finished_aio (TYPE_1__*) ; 
 int /*<<< orphan*/  tl_aio_query_restart (int /*<<< orphan*/ ) ; 

void tl_aio_query_restart_all_finished (void) {
  while (finished_aio_queue) {
    tl_aio_query_restart (finished_aio_queue->x);
    finished_aio_queue = queue_del_first_finished_aio (finished_aio_queue);
  }
}