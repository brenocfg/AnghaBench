#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  dump_obj_relocations (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * globallist_curr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * globallist_next (int /*<<< orphan*/ *) ; 

void
dump_relocations (Obj_Entry *obj0)
{
    Obj_Entry *obj;

    for (obj = globallist_curr(obj0); obj != NULL;
      obj = globallist_next(obj)) {
        dump_obj_relocations(obj);
    }
}