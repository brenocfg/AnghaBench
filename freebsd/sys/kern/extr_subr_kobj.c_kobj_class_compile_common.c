#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kobj_ops_t ;
struct TYPE_9__ {TYPE_1__* desc; } ;
typedef  TYPE_3__ kobj_method_t ;
typedef  TYPE_4__* kobj_class_t ;
struct TYPE_10__ {TYPE_2__* ops; TYPE_3__* methods; } ;
struct TYPE_8__ {TYPE_4__* cls; int /*<<< orphan*/ ** cache; } ;
struct TYPE_7__ {scalar_t__ id; } ;

/* Variables and functions */
 int KOBJ_CACHE_SIZE ; 
 int /*<<< orphan*/  kobj_next_id ; 
 int /*<<< orphan*/  null_method ; 

__attribute__((used)) static void
kobj_class_compile_common(kobj_class_t cls, kobj_ops_t ops)
{
	kobj_method_t *m;
	int i;

	/*
	 * Don't do anything if we are already compiled.
	 */
	if (cls->ops)
		return;

	/*
	 * First register any methods which need it.
	 */
	for (i = 0, m = cls->methods; m->desc; i++, m++) {
		if (m->desc->id == 0)
			m->desc->id = kobj_next_id++;
	}

	/*
	 * Then initialise the ops table.
	 */
	for (i = 0; i < KOBJ_CACHE_SIZE; i++)
		ops->cache[i] = &null_method;
	ops->cls = cls;
	cls->ops = ops;
}