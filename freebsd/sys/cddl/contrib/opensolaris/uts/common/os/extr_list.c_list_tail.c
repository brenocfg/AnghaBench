#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  list_prev; } ;
struct TYPE_7__ {TYPE_1__ list_head; } ;
typedef  TYPE_2__ list_t ;

/* Variables and functions */
 scalar_t__ list_empty (TYPE_2__*) ; 
 void* list_object (TYPE_2__*,int /*<<< orphan*/ ) ; 

void *
list_tail(list_t *list)
{
	if (list_empty(list))
		return (NULL);
	return (list_object(list, list->list_head.list_prev));
}