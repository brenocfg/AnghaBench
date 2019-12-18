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
struct link_map {struct link_map* l_next; struct link_map* l_prev; int /*<<< orphan*/  l_offs; int /*<<< orphan*/  l_ld; int /*<<< orphan*/  l_addr; int /*<<< orphan*/  l_name; } ;
struct TYPE_7__ {struct link_map linkmap; } ;
struct TYPE_6__ {struct link_map* r_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  relocbase; struct link_map linkmap; int /*<<< orphan*/  dynamic; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 TYPE_3__ obj_rtld ; 
 TYPE_2__ r_debug ; 

__attribute__((used)) static void
linkmap_add(Obj_Entry *obj)
{
    struct link_map *l = &obj->linkmap;
    struct link_map *prev;

    obj->linkmap.l_name = obj->path;
    obj->linkmap.l_addr = obj->mapbase;
    obj->linkmap.l_ld = obj->dynamic;
#ifdef __mips__
    /* GDB needs load offset on MIPS to use the symbols */
    obj->linkmap.l_offs = obj->relocbase;
#endif

    if (r_debug.r_map == NULL) {
	r_debug.r_map = l;
	return;
    }

    /*
     * Scan to the end of the list, but not past the entry for the
     * dynamic linker, which we want to keep at the very end.
     */
    for (prev = r_debug.r_map;
      prev->l_next != NULL && prev->l_next != &obj_rtld.linkmap;
      prev = prev->l_next)
	;

    /* Link in the new entry. */
    l->l_prev = prev;
    l->l_next = prev->l_next;
    if (l->l_next != NULL)
	l->l_next->l_prev = l;
    prev->l_next = l;
}