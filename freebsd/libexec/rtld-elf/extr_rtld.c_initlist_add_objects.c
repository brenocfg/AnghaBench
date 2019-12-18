#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int init_scanned; scalar_t__ fini; scalar_t__ fini_array; int on_fini_list; int /*<<< orphan*/ * needed_aux_filtees; int /*<<< orphan*/ * needed_filtees; int /*<<< orphan*/ * needed; scalar_t__ init_done; } ;
typedef  int /*<<< orphan*/  Objlist ;
typedef  TYPE_1__ Obj_Entry ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 TYPE_1__* globallist_next (TYPE_1__*) ; 
 int /*<<< orphan*/  initlist_add_neededs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_fini ; 
 int /*<<< orphan*/  objlist_push_head (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  objlist_push_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
initlist_add_objects(Obj_Entry *obj, Obj_Entry *tail, Objlist *list)
{
    Obj_Entry *nobj;

    if (obj->init_scanned || obj->init_done)
	return;
    obj->init_scanned = true;

    /* Recursively process the successor objects. */
    nobj = globallist_next(obj);
    if (nobj != NULL && obj != tail)
	initlist_add_objects(nobj, tail, list);

    /* Recursively process the needed objects. */
    if (obj->needed != NULL)
	initlist_add_neededs(obj->needed, list);
    if (obj->needed_filtees != NULL)
	initlist_add_neededs(obj->needed_filtees, list);
    if (obj->needed_aux_filtees != NULL)
	initlist_add_neededs(obj->needed_aux_filtees, list);

    /* Add the object to the init list. */
    objlist_push_tail(list, obj);

    /* Add the object to the global fini list in the reverse order. */
    if ((obj->fini != (Elf_Addr)NULL || obj->fini_array != (Elf_Addr)NULL)
      && !obj->on_fini_list) {
	objlist_push_head(&list_fini, obj);
	obj->on_fini_list = true;
    }
}