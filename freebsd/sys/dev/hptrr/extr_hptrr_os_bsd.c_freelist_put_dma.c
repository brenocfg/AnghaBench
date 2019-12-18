#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct freelist {void* head; int /*<<< orphan*/  count; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  BUS_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  HPT_ASSERT (int /*<<< orphan*/ ) ; 

void freelist_put_dma(struct freelist *list, void *p, BUS_ADDRESS busaddr)
{
    HPT_ASSERT(list->dma);
    list->count++;
    *(void **)p = list->head;
    *(BUS_ADDRESS *)((void **)p+1) = busaddr;
    list->head = p;
}