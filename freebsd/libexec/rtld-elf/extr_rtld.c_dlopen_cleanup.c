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
struct TYPE_5__ {scalar_t__ refcount; int /*<<< orphan*/  dl_refcount; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  unload_object (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unref_dag (TYPE_1__*) ; 

__attribute__((used)) static void
dlopen_cleanup(Obj_Entry *obj, RtldLockState *lockstate)
{

	obj->dl_refcount--;
	unref_dag(obj);
	if (obj->refcount == 0)
		unload_object(obj, lockstate);
}