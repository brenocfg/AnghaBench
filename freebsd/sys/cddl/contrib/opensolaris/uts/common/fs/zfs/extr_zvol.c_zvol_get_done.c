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
struct TYPE_5__ {int /*<<< orphan*/  zgd_lr; scalar_t__ zgd_db; } ;
typedef  TYPE_1__ zgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rangelock_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zvol_get_done(zgd_t *zgd, int error)
{
	if (zgd->zgd_db)
		dmu_buf_rele(zgd->zgd_db, zgd);

	rangelock_exit(zgd->zgd_lr);

	kmem_free(zgd, sizeof (zgd_t));
}