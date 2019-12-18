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
typedef  scalar_t__ linker_class_t ;
typedef  TYPE_1__* kobj_class_t ;
struct TYPE_3__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  classes ; 
 int /*<<< orphan*/  kobj_class_compile (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 
 int linker_no_more_classes ; 

int
linker_add_class(linker_class_t lc)
{

	/*
	 * We disallow any class registration past SI_ORDER_ANY
	 * of SI_SUB_KLD.  We bump the reference count to keep the
	 * ops from being freed.
	 */
	if (linker_no_more_classes == 1)
		return (EPERM);
	kobj_class_compile((kobj_class_t) lc);
	((kobj_class_t)lc)->refs++;	/* XXX: kobj_mtx */
	TAILQ_INSERT_TAIL(&classes, lc, link);
	return (0);
}