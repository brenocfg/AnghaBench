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
struct TYPE_6__ {TYPE_1__* prev; TYPE_3__* next; } ;
typedef  TYPE_2__ levelitem_t ;
struct TYPE_7__ {TYPE_1__* prev; } ;
struct TYPE_5__ {TYPE_3__* next; } ;

/* Variables and functions */
 TYPE_3__* levelitems ; 

void RemoveLevelItemFromList(levelitem_t *li)
{
	if (li->prev) li->prev->next = li->next;
	else levelitems = li->next;
	if (li->next) li->next->prev = li->prev;
}