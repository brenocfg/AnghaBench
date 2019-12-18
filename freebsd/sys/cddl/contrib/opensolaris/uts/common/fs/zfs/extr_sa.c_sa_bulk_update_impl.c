#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* sa_update_cb ) (TYPE_3__*,int /*<<< orphan*/ *) ;scalar_t__ sa_need_attr_registration; } ;
typedef  TYPE_2__ sa_os_t ;
struct TYPE_13__ {int /*<<< orphan*/  sa_lock; TYPE_1__* sa_os; } ;
typedef  TYPE_3__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;
struct TYPE_11__ {TYPE_2__* os_sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  IS_SA_BONUSTYPE (int /*<<< orphan*/ ) ; 
 TYPE_3__* MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_BONUS ; 
 int /*<<< orphan*/  SA_BONUSTYPE_FROM_DB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_GET_DB (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_UPDATE ; 
 int sa_attr_op (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_attr_register_sync (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sa_bulk_update_impl(sa_handle_t *hdl, sa_bulk_attr_t *bulk, int count,
    dmu_tx_t *tx)
{
	int error;
	sa_os_t *sa = hdl->sa_os->os_sa;
	dmu_object_type_t bonustype;

	bonustype = SA_BONUSTYPE_FROM_DB(SA_GET_DB(hdl, SA_BONUS));

	ASSERT(hdl);
	ASSERT(MUTEX_HELD(&hdl->sa_lock));

	/* sync out registration table if necessary */
	if (sa->sa_need_attr_registration)
		sa_attr_register_sync(hdl, tx);

	error = sa_attr_op(hdl, bulk, count, SA_UPDATE, tx);
	if (error == 0 && !IS_SA_BONUSTYPE(bonustype) && sa->sa_update_cb)
		sa->sa_update_cb(hdl, tx);

	return (error);
}