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
struct TYPE_3__ {int tail; int capacity; scalar_t__ size; scalar_t__ head; } ;
typedef  TYPE_1__ GDnsQueue ;

/* Variables and functions */

void
gqueue_init (GDnsQueue * q, int capacity)
{
  q->head = 0;
  q->tail = -1;
  q->size = 0;
  q->capacity = capacity;
}