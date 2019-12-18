#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* prev; TYPE_1__* next; } ;
typedef  TYPE_3__ dlist_entry ;
struct TYPE_6__ {TYPE_1__* next; } ;
struct TYPE_5__ {TYPE_2__* prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void dlist_remove(dlist_entry *item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}