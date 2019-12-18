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
typedef  int /*<<< orphan*/  kobj_t ;
typedef  TYPE_1__* kobj_class_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_LOCK () ; 
 int /*<<< orphan*/  KOBJ_UNLOCK () ; 
 int kobj_class_compile1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kobj_init_common (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
kobj_init1(kobj_t obj, kobj_class_t cls, int mflags)
{
	int error;

	KOBJ_LOCK();
	while (cls->ops == NULL) {
		/*
		 * kobj_class_compile doesn't want the lock held
		 * because of the call to malloc - we drop the lock
		 * and re-try.
		 */
		KOBJ_UNLOCK();
		error = kobj_class_compile1(cls, mflags);
		if (error != 0)
			return (error);
		KOBJ_LOCK();
	}
	kobj_init_common(obj, cls);
	KOBJ_UNLOCK();
	return (0);
}