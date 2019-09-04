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
struct TYPE_4__ {int tail; int capacity; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ GDnsQueue ;

/* Variables and functions */
 scalar_t__ gqueue_full (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int
gqueue_enqueue (GDnsQueue * q, char *item)
{
  if (gqueue_full (q))
    return -1;

  q->tail = (q->tail + 1) % q->capacity;
  strcpy (q->buffer[q->tail], item);
  q->size++;
  return 0;
}