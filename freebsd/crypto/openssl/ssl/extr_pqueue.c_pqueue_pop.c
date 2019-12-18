#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* items; } ;
typedef  TYPE_1__ pqueue ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ pitem ;

/* Variables and functions */

pitem *pqueue_pop(pqueue *pq)
{
    pitem *item = pq->items;

    if (pq->items != NULL)
        pq->items = pq->items->next;

    return item;
}