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
struct TYPE_4__ {int /*<<< orphan*/ * ev_first; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 TYPE_1__* qs ; 
 int /*<<< orphan*/  queues_cnt ; 

void queue_free (queue *q) {
  queues_cnt--;
  q->ev_first = (event *)qs;
  qs = q;
}