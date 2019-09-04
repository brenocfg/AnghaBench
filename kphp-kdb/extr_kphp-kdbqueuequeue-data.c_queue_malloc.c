#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ev_first; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 scalar_t__ dl_get_memory_used () ; 
 TYPE_1__* dl_malloc0 (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* qs ; 
 int /*<<< orphan*/  queues_cnt ; 
 int /*<<< orphan*/  queues_memory ; 

queue *queue_malloc (void) {
  queues_cnt++;
  if (qs == NULL) {
    queues_memory -= dl_get_memory_used();
    queue *res = dl_malloc0 (sizeof (queue));
    queues_memory += dl_get_memory_used();

    return res;
  }
  queue *res = qs;
  qs = (queue *)qs->ev_first;
  memset (res, 0, sizeof (queue));

  return res;
}