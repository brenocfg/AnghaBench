#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int filtees_loaded; int /*<<< orphan*/  needed_aux_filtees; int /*<<< orphan*/  needed_filtees; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  load_filtee1 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_restart_for_upgrade (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
load_filtees(Obj_Entry *obj, int flags, RtldLockState *lockstate)
{

    lock_restart_for_upgrade(lockstate);
    if (!obj->filtees_loaded) {
	load_filtee1(obj, obj->needed_filtees, flags, lockstate);
	load_filtee1(obj, obj->needed_aux_filtees, flags, lockstate);
	obj->filtees_loaded = true;
    }
}