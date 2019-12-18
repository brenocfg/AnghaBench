#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int filtees_loaded; int /*<<< orphan*/ * needed_aux_filtees; int /*<<< orphan*/ * needed_filtees; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  free_needed_filtees (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unload_filtees(Obj_Entry *obj, RtldLockState *lockstate)
{

	free_needed_filtees(obj->needed_filtees, lockstate);
	obj->needed_filtees = NULL;
	free_needed_filtees(obj->needed_aux_filtees, lockstate);
	obj->needed_aux_filtees = NULL;
	obj->filtees_loaded = false;
}