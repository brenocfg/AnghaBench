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
struct freelist {scalar_t__ dma; void* head; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPT_ASSERT (int) ; 

void freelist_put(struct freelist * list, void *p)
{
    HPT_ASSERT(list->dma==0);
    list->count++;
    *(void **)p = list->head;
    list->head = p;
}