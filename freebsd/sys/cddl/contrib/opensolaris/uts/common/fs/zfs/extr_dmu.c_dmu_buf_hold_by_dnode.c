#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 int DB_RF_CANFAIL ; 
 int DB_RF_NOPREFETCH ; 
 int DMU_READ_NO_PREFETCH ; 
 int dbuf_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbuf_rele (int /*<<< orphan*/ *,void*) ; 
 int dmu_buf_hold_noread_by_dnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

int
dmu_buf_hold_by_dnode(dnode_t *dn, uint64_t offset,
    void *tag, dmu_buf_t **dbp, int flags)
{
	int err;
	int db_flags = DB_RF_CANFAIL;

	if (flags & DMU_READ_NO_PREFETCH)
		db_flags |= DB_RF_NOPREFETCH;

	err = dmu_buf_hold_noread_by_dnode(dn, offset, tag, dbp);
	if (err == 0) {
		dmu_buf_impl_t *db = (dmu_buf_impl_t *)(*dbp);
		err = dbuf_read(db, NULL, db_flags);
		if (err != 0) {
			dbuf_rele(db, tag);
			*dbp = NULL;
		}
	}

	return (err);
}