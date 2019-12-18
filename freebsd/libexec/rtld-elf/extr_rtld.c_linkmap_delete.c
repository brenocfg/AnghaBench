#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct link_map {TYPE_2__* l_prev; TYPE_1__* l_next; } ;
struct TYPE_9__ {TYPE_1__* r_map; } ;
struct TYPE_8__ {struct link_map linkmap; } ;
struct TYPE_7__ {TYPE_1__* l_next; } ;
struct TYPE_6__ {TYPE_2__* l_prev; } ;
typedef  TYPE_3__ Obj_Entry ;

/* Variables and functions */
 TYPE_4__ r_debug ; 

__attribute__((used)) static void
linkmap_delete(Obj_Entry *obj)
{
    struct link_map *l = &obj->linkmap;

    if (l->l_prev == NULL) {
	if ((r_debug.r_map = l->l_next) != NULL)
	    l->l_next->l_prev = NULL;
	return;
    }

    if ((l->l_prev->l_next = l->l_next) != NULL)
	l->l_next->l_prev = l->l_prev;
}