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
struct TYPE_5__ {struct TYPE_5__* key; struct TYPE_5__* value; struct TYPE_5__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_6__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 

void  FreeValueKeys(entity_t *ent)
{
	epair_t	*ep,*next;

	for (ep=ent->epairs ; ep ; ep=next)
	{
		next = ep->next;
		FreeMemory(ep->value);
		FreeMemory(ep->key);
		FreeMemory(ep);
	}
	ent->epairs = NULL;
}