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
struct TYPE_5__ {scalar_t__ holdcount; int unholdfree; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  linkmap_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_free (TYPE_1__*) ; 

__attribute__((used)) static void
release_object(Obj_Entry *obj)
{

	if (obj->holdcount > 0) {
		obj->unholdfree = true;
		return;
	}
	munmap(obj->mapbase, obj->mapsize);
	linkmap_delete(obj);
	obj_free(obj);
}