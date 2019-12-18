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
struct TYPE_4__ {char** buffer; size_t head; int capacity; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ GDnsQueue ;

/* Variables and functions */
 scalar_t__ gqueue_empty (TYPE_1__*) ; 

char *
gqueue_dequeue (GDnsQueue * q)
{
  char *item;
  if (gqueue_empty (q))
    return NULL;

  item = q->buffer[q->head];
  q->head = (q->head + 1) % q->capacity;
  q->size--;
  return item;
}