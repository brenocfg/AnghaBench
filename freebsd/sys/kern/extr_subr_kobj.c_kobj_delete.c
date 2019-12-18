#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct malloc_type {int dummy; } ;
typedef  TYPE_2__* kobj_t ;
typedef  TYPE_3__* kobj_class_t ;
struct TYPE_9__ {int refs; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {TYPE_3__* cls; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KOBJ_LOCK () ; 
 int /*<<< orphan*/  KOBJ_UNLOCK () ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  free (TYPE_2__*,struct malloc_type*) ; 
 int /*<<< orphan*/  kobj_class_free (TYPE_3__*) ; 

void
kobj_delete(kobj_t obj, struct malloc_type *mtype)
{
	kobj_class_t cls = obj->ops->cls;
	int refs;

	/*
	 * Consider freeing the compiled method table for the class
	 * after its last instance is deleted. As an optimisation, we
	 * should defer this for a short while to avoid thrashing.
	 */
	KOBJ_ASSERT(MA_NOTOWNED);
	KOBJ_LOCK();
	cls->refs--;
	refs = cls->refs;
	KOBJ_UNLOCK();

	if (!refs)
		kobj_class_free(cls);

	obj->ops = NULL;
	if (mtype)
		free(obj, mtype);
}