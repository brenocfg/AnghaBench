#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* piterator ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ pitem ;

/* Variables and functions */

pitem *pqueue_next(piterator *item)
{
    pitem *ret;

    if (item == NULL || *item == NULL)
        return NULL;

    /* *item != NULL */
    ret = *item;
    *item = (*item)->next;

    return ret;
}