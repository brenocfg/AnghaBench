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
typedef  TYPE_1__* vm_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * cred; scalar_t__ charge; } ;

/* Variables and functions */
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_zone ; 
 int /*<<< orphan*/  swap_release_by_cred (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
vm_object_destroy(vm_object_t object)
{

	/*
	 * Release the allocation charge.
	 */
	if (object->cred != NULL) {
		swap_release_by_cred(object->charge, object->cred);
		object->charge = 0;
		crfree(object->cred);
		object->cred = NULL;
	}

	/*
	 * Free the space for the object.
	 */
	uma_zfree(obj_zone, object);
}