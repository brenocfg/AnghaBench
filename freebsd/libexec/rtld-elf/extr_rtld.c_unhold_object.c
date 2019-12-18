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
struct TYPE_4__ {scalar_t__ holdcount; scalar_t__ unholdfree; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  release_object (TYPE_1__*) ; 

__attribute__((used)) static void
unhold_object(Obj_Entry *obj)
{

	assert(obj->holdcount > 0);
	if (--obj->holdcount == 0 && obj->unholdfree)
		release_object(obj);
}