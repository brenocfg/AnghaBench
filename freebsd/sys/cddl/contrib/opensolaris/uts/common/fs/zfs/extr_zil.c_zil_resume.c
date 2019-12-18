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
struct TYPE_3__ {scalar_t__ zl_suspend; int /*<<< orphan*/  zl_lock; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_objset_zil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_long_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_tag ; 

void
zil_resume(void *cookie)
{
	objset_t *os = cookie;
	zilog_t *zilog = dmu_objset_zil(os);

	mutex_enter(&zilog->zl_lock);
	ASSERT(zilog->zl_suspend != 0);
	zilog->zl_suspend--;
	mutex_exit(&zilog->zl_lock);
	dsl_dataset_long_rele(dmu_objset_ds(os), suspend_tag);
	dsl_dataset_rele(dmu_objset_ds(os), suspend_tag);
}