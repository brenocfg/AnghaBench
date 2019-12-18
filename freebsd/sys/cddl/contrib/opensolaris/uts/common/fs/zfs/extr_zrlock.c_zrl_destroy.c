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
struct TYPE_3__ {int /*<<< orphan*/  zr_cv; int /*<<< orphan*/  zr_refcount; int /*<<< orphan*/  zr_mtx; } ;
typedef  TYPE_1__ zrlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZRL_DESTROYED ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
zrl_destroy(zrlock_t *zrl)
{
	ASSERT0(zrl->zr_refcount);

	mutex_destroy(&zrl->zr_mtx);
	zrl->zr_refcount = ZRL_DESTROYED;
	cv_destroy(&zrl->zr_cv);
}