#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sa_master_obj; scalar_t__ sa_layout_attr_obj; int /*<<< orphan*/  sa_force_spill; } ;
typedef  TYPE_1__ sa_os_t ;
struct TYPE_11__ {TYPE_8__* tx_objset; } ;
typedef  TYPE_2__ dmu_tx_t ;
struct TYPE_12__ {TYPE_1__* os_sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_NEW_OBJECT ; 
 int DN_OLD_MAX_BONUSLEN ; 
 int /*<<< orphan*/ * SA_LAYOUTS ; 
 int /*<<< orphan*/ * SA_REGISTRY ; 
 int /*<<< orphan*/  THT_SPILL ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_object_impl (TYPE_2__*,TYPE_8__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_sa_registration_hold (TYPE_1__*,TYPE_2__*) ; 

void
dmu_tx_hold_sa_create(dmu_tx_t *tx, int attrsize)
{
	sa_os_t *sa = tx->tx_objset->os_sa;

	dmu_tx_hold_bonus(tx, DMU_NEW_OBJECT);

	if (tx->tx_objset->os_sa->sa_master_obj == 0)
		return;

	if (tx->tx_objset->os_sa->sa_layout_attr_obj) {
		dmu_tx_hold_zap(tx, sa->sa_layout_attr_obj, B_TRUE, NULL);
	} else {
		dmu_tx_hold_zap(tx, sa->sa_master_obj, B_TRUE, SA_LAYOUTS);
		dmu_tx_hold_zap(tx, sa->sa_master_obj, B_TRUE, SA_REGISTRY);
		dmu_tx_hold_zap(tx, DMU_NEW_OBJECT, B_TRUE, NULL);
		dmu_tx_hold_zap(tx, DMU_NEW_OBJECT, B_TRUE, NULL);
	}

	dmu_tx_sa_registration_hold(sa, tx);

	if (attrsize <= DN_OLD_MAX_BONUSLEN && !sa->sa_force_spill)
		return;

	(void) dmu_tx_hold_object_impl(tx, tx->tx_objset, DMU_NEW_OBJECT,
	    THT_SPILL, 0, 0);
}