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
typedef  TYPE_1__* vm_object_t ;
struct TYPE_3__ {int flags; scalar_t__ type; } ;

/* Variables and functions */
 int MADV_FREE ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 int OBJ_ONEMAPPING ; 
 int OBJ_UNMANAGED ; 

__attribute__((used)) static bool
vm_object_advice_applies(vm_object_t object, int advice)
{

	if ((object->flags & OBJ_UNMANAGED) != 0)
		return (false);
	if (advice != MADV_FREE)
		return (true);
	return ((object->type == OBJT_DEFAULT || object->type == OBJT_SWAP) &&
	    (object->flags & OBJ_ONEMAPPING) != 0);
}