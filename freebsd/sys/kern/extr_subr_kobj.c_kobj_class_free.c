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
typedef  TYPE_1__* kobj_class_t ;
struct TYPE_3__ {scalar_t__ refs; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KOBJ_LOCK () ; 
 int /*<<< orphan*/  KOBJ_UNLOCK () ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_KOBJ ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 

void
kobj_class_free(kobj_class_t cls)
{
	void* ops = NULL;

	KOBJ_ASSERT(MA_NOTOWNED);
	KOBJ_LOCK();

	/*
	 * Protect against a race between kobj_create and
	 * kobj_delete.
	 */
	if (cls->refs == 0) {
		/*
		 * For now we don't do anything to unregister any methods
		 * which are no longer used.
		 */

		/*
		 * Free memory and clean up.
		 */
		ops = cls->ops;
		cls->ops = NULL;
	}
	
	KOBJ_UNLOCK();

	if (ops)
		free(ops, M_KOBJ);
}