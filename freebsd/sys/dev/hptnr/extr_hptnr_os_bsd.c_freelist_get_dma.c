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
struct freelist {int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  BUS_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  HPT_ASSERT (int /*<<< orphan*/ ) ; 
 void* freelist_get (struct freelist*) ; 

void *freelist_get_dma(struct freelist *list, BUS_ADDRESS *busaddr)
{
    void *result;
    HPT_ASSERT(list->dma);
    result = freelist_get(list);
    if (result)
        *busaddr = *(BUS_ADDRESS *)((void **)result+1);
    return result;
}