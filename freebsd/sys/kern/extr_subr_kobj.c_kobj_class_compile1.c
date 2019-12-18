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
struct kobj_ops {int dummy; } ;
typedef  int /*<<< orphan*/ * kobj_ops_t ;
typedef  TYPE_1__* kobj_class_t ;
struct TYPE_4__ {scalar_t__ ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KOBJ_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KOBJ_LOCK () ; 
 int /*<<< orphan*/  KOBJ_UNLOCK () ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_KOBJ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_class_compile_common (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kobj_class_compile1(kobj_class_t cls, int mflags)
{
	kobj_ops_t ops;

	KOBJ_ASSERT(MA_NOTOWNED);

	ops = malloc(sizeof(struct kobj_ops), M_KOBJ, mflags);
	if (ops == NULL)
		return (ENOMEM);

	/*
	 * We may have lost a race for kobj_class_compile here - check
	 * to make sure someone else hasn't already compiled this
	 * class.
	 */
	KOBJ_LOCK();
	if (cls->ops) {
		KOBJ_UNLOCK();
		free(ops, M_KOBJ);
		return (0);
	}
	kobj_class_compile_common(cls, ops);
	KOBJ_UNLOCK();
	return (0);
}