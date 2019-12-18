#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list_head; } ;
typedef  TYPE_1__ list_t ;
struct TYPE_8__ {int /*<<< orphan*/ * list_prev; } ;
typedef  TYPE_2__ list_node_t ;

/* Variables and functions */
 TYPE_2__* list_d2l (TYPE_1__*,void*) ; 
 void* list_object (TYPE_1__*,int /*<<< orphan*/ *) ; 

void *
list_prev(list_t *list, void *object)
{
	list_node_t *node = list_d2l(list, object);

	if (node->list_prev != &list->list_head)
		return (list_object(list, node->list_prev));

	return (NULL);
}