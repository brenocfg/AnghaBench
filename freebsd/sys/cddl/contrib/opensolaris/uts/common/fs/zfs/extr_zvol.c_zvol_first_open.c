#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zv_flags; int /*<<< orphan*/  zv_name; int /*<<< orphan*/  zv_zilog; int /*<<< orphan*/  zv_dn; int /*<<< orphan*/  zv_volblocksize; int /*<<< orphan*/ * zv_objset; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {int /*<<< orphan*/  doi_data_block_size; } ;
typedef  TYPE_2__ dmu_object_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZVOL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int /*<<< orphan*/  ZVOL_RDONLY ; 
 int /*<<< orphan*/  ZVOL_ZAP_OBJ ; 
 int dmu_object_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int dmu_objset_own (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_prop_get_integer (int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zil_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_get_data ; 
 int /*<<< orphan*/  zvol_size_changed (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zvol_tag ; 

int
zvol_first_open(zvol_state_t *zv)
{
	dmu_object_info_t doi;
	objset_t *os;
	uint64_t volsize;
	int error;
	uint64_t readonly;

	/* lie and say we're read-only */
	error = dmu_objset_own(zv->zv_name, DMU_OST_ZVOL, B_TRUE,
	    zvol_tag, &os);
	if (error)
		return (error);

	zv->zv_objset = os;
	error = zap_lookup(os, ZVOL_ZAP_OBJ, "size", 8, 1, &volsize);
	if (error) {
		ASSERT(error == 0);
		dmu_objset_disown(os, zvol_tag);
		return (error);
	}

	/* get and cache the blocksize */
	error = dmu_object_info(os, ZVOL_OBJ, &doi);
	if (error) {
		ASSERT(error == 0);
		dmu_objset_disown(os, zvol_tag);
		return (error);
	}
	zv->zv_volblocksize = doi.doi_data_block_size;

	error = dnode_hold(os, ZVOL_OBJ, zvol_tag, &zv->zv_dn);
	if (error) {
		dmu_objset_disown(os, zvol_tag);
		return (error);
	}

	zvol_size_changed(zv, volsize);
	zv->zv_zilog = zil_open(os, zvol_get_data);

	VERIFY(dsl_prop_get_integer(zv->zv_name, "readonly", &readonly,
	    NULL) == 0);
	if (readonly || dmu_objset_is_snapshot(os) ||
	    !spa_writeable(dmu_objset_spa(os)))
		zv->zv_flags |= ZVOL_RDONLY;
	else
		zv->zv_flags &= ~ZVOL_RDONLY;
	return (error);
}