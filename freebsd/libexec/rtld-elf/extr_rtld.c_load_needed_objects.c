#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  needed; scalar_t__ marker; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int process_needed (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
load_needed_objects(Obj_Entry *first, int flags)
{
    Obj_Entry *obj;

    for (obj = first; obj != NULL; obj = TAILQ_NEXT(obj, next)) {
	if (obj->marker)
	    continue;
	if (process_needed(obj, obj->needed, flags) == -1)
	    return (-1);
    }
    return (0);
}