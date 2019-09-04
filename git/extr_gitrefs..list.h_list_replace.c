#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {TYPE_2__* next; TYPE_1__* prev; } ;
struct TYPE_4__ {struct list_head* prev; } ;
struct TYPE_3__ {struct list_head* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void list_replace(struct list_head *old, struct list_head *newp)
{
	newp->next = old->next;
	newp->prev = old->prev;
	newp->prev->next = newp;
	newp->next->prev = newp;
}