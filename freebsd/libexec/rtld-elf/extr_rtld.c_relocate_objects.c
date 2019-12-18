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
struct TYPE_8__ {scalar_t__ marker; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int relocate_object (TYPE_1__*,int,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
relocate_objects(Obj_Entry *first, bool bind_now, Obj_Entry *rtldobj,
    int flags, RtldLockState *lockstate)
{
	Obj_Entry *obj;
	int error;

	for (error = 0, obj = first;  obj != NULL;
	    obj = TAILQ_NEXT(obj, next)) {
		if (obj->marker)
			continue;
		error = relocate_object(obj, bind_now, rtldobj, flags,
		    lockstate);
		if (error == -1)
			break;
	}
	return (error);
}