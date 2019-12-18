#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ifuncs_resolved; scalar_t__ gnu_ifunc; scalar_t__ bind_now; scalar_t__ irelative; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int obj_disable_relro (TYPE_1__*) ; 
 int obj_enforce_relro (TYPE_1__*) ; 
 int reloc_gnu_ifunc (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int reloc_iresolve (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
resolve_object_ifunc(Obj_Entry *obj, bool bind_now, int flags,
    RtldLockState *lockstate)
{

	if (obj->ifuncs_resolved)
		return (0);
	obj->ifuncs_resolved = true;
	if (!obj->irelative && !((obj->bind_now || bind_now) && obj->gnu_ifunc))
		return (0);
	if (obj_disable_relro(obj) == -1 ||
	    (obj->irelative && reloc_iresolve(obj, lockstate) == -1) ||
	    ((obj->bind_now || bind_now) && obj->gnu_ifunc &&
	    reloc_gnu_ifunc(obj, flags, lockstate) == -1) ||
	    obj_enforce_relro(obj) == -1)
		return (-1);
	return (0);
}