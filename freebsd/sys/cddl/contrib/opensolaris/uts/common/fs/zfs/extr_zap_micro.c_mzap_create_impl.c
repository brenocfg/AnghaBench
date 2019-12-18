#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_t ;
typedef  scalar_t__ zap_flags_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {uintptr_t mz_salt; int mz_normflags; int /*<<< orphan*/  mz_block_type; } ;
typedef  TYPE_1__ mzap_phys_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_8__ {TYPE_1__* db_data; } ;
typedef  TYPE_2__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DMU_READ_NO_PREFETCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBT_MICRO ; 
 int /*<<< orphan*/  dmu_buf_hold (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_upgrade (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zap_lockdir_impl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zap_unlockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mzap_create_impl(objset_t *os, uint64_t obj, int normflags, zap_flags_t flags,
    dmu_tx_t *tx)
{
	dmu_buf_t *db;

	VERIFY0(dmu_buf_hold(os, obj, 0, FTAG, &db, DMU_READ_NO_PREFETCH));

	dmu_buf_will_dirty(db, tx);
	mzap_phys_t *zp = db->db_data;
	zp->mz_block_type = ZBT_MICRO;
	zp->mz_salt = ((uintptr_t)db ^ (uintptr_t)tx ^ (obj << 1)) | 1ULL;
	zp->mz_normflags = normflags;

	if (flags != 0) {
		zap_t *zap;
		/* Only fat zap supports flags; upgrade immediately. */
		VERIFY0(zap_lockdir_impl(db, FTAG, tx, RW_WRITER,
		    B_FALSE, B_FALSE, &zap));
		VERIFY0(mzap_upgrade(&zap, FTAG, tx, flags));
		zap_unlockdir(zap, FTAG);
	} else {
		dmu_buf_rele(db, FTAG);
	}
}