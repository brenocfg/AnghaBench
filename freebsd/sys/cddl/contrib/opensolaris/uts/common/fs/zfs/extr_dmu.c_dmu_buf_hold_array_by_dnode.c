#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_18__ {int dn_datablkshift; scalar_t__ dn_datablksz; int /*<<< orphan*/  dn_struct_rwlock; int /*<<< orphan*/  dn_zfetch; TYPE_2__* dn_objset; scalar_t__ dn_object; } ;
typedef  TYPE_4__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_19__ {scalar_t__ db_state; int /*<<< orphan*/  db_mtx; int /*<<< orphan*/  db_changed; int /*<<< orphan*/  db; } ;
typedef  TYPE_5__ dmu_buf_impl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  ru_oublock; } ;
struct TYPE_16__ {int /*<<< orphan*/  os_spa; TYPE_1__* os_dsl_dataset; } ;
struct TYPE_15__ {scalar_t__ ds_object; } ;
struct TYPE_14__ {TYPE_3__ td_ru; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DB_FILL ; 
 scalar_t__ DB_READ ; 
 int DB_RF_CANFAIL ; 
 int DB_RF_HAVESTRUCT ; 
 int DB_RF_NEVERWAIT ; 
 int DB_RF_NOPREFETCH ; 
 scalar_t__ DB_UNCACHED ; 
 scalar_t__ DMU_MAX_ACCESS ; 
 int DMU_READ_NO_PREFETCH ; 
 scalar_t__ DNODE_IS_CACHEABLE (TYPE_4__*) ; 
 scalar_t__ DNODE_META_IS_CACHEABLE (TYPE_4__*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int P2ALIGN (scalar_t__,unsigned long long) ; 
 int P2ROUNDUP (scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RACCT_WRITEBPS ; 
 int /*<<< orphan*/  RACCT_WRITEIOPS ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 int /*<<< orphan*/  curproc ; 
 TYPE_11__* curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* dbuf_hold (TYPE_4__*,scalar_t__,void*) ; 
 int /*<<< orphan*/  dbuf_read (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dbuf_whichblock (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmu_buf_rele_array (int /*<<< orphan*/ **,scalar_t__,void*) ; 
 int /*<<< orphan*/  dmu_zfetch (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ ** kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  racct_add_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfetch_array_rd_sz ; 
 int /*<<< orphan*/  zfs_panic_recover (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zio_wait (int /*<<< orphan*/ *) ; 

int
dmu_buf_hold_array_by_dnode(dnode_t *dn, uint64_t offset, uint64_t length,
    boolean_t read, void *tag, int *numbufsp, dmu_buf_t ***dbpp, uint32_t flags)
{
	dmu_buf_t **dbp;
	uint64_t blkid, nblks, i;
	uint32_t dbuf_flags;
	int err;
	zio_t *zio;

	ASSERT(length <= DMU_MAX_ACCESS);

	/*
	 * Note: We directly notify the prefetch code of this read, so that
	 * we can tell it about the multi-block read.  dbuf_read() only knows
	 * about the one block it is accessing.
	 */
	dbuf_flags = DB_RF_CANFAIL | DB_RF_NEVERWAIT | DB_RF_HAVESTRUCT |
	    DB_RF_NOPREFETCH;

	rw_enter(&dn->dn_struct_rwlock, RW_READER);
	if (dn->dn_datablkshift) {
		int blkshift = dn->dn_datablkshift;
		nblks = (P2ROUNDUP(offset + length, 1ULL << blkshift) -
		    P2ALIGN(offset, 1ULL << blkshift)) >> blkshift;
	} else {
		if (offset + length > dn->dn_datablksz) {
			zfs_panic_recover("zfs: accessing past end of object "
			    "%llx/%llx (size=%u access=%llu+%llu)",
			    (longlong_t)dn->dn_objset->
			    os_dsl_dataset->ds_object,
			    (longlong_t)dn->dn_object, dn->dn_datablksz,
			    (longlong_t)offset, (longlong_t)length);
			rw_exit(&dn->dn_struct_rwlock);
			return (SET_ERROR(EIO));
		}
		nblks = 1;
	}
	dbp = kmem_zalloc(sizeof (dmu_buf_t *) * nblks, KM_SLEEP);

#if defined(_KERNEL) && defined(RACCT)
	if (racct_enable && !read) {
		PROC_LOCK(curproc);
		racct_add_force(curproc, RACCT_WRITEBPS, length);
		racct_add_force(curproc, RACCT_WRITEIOPS, nblks);
		PROC_UNLOCK(curproc);
	}
#endif

	zio = zio_root(dn->dn_objset->os_spa, NULL, NULL, ZIO_FLAG_CANFAIL);
	blkid = dbuf_whichblock(dn, 0, offset);
	for (i = 0; i < nblks; i++) {
		dmu_buf_impl_t *db = dbuf_hold(dn, blkid + i, tag);
		if (db == NULL) {
			rw_exit(&dn->dn_struct_rwlock);
			dmu_buf_rele_array(dbp, nblks, tag);
			zio_nowait(zio);
			return (SET_ERROR(EIO));
		}

		/* initiate async i/o */
		if (read)
			(void) dbuf_read(db, zio, dbuf_flags);
#ifdef _KERNEL
		else
			curthread->td_ru.ru_oublock++;
#endif
		dbp[i] = &db->db;
	}

	if ((flags & DMU_READ_NO_PREFETCH) == 0 &&
	    DNODE_META_IS_CACHEABLE(dn) && length <= zfetch_array_rd_sz) {
		dmu_zfetch(&dn->dn_zfetch, blkid, nblks,
		    read && DNODE_IS_CACHEABLE(dn));
	}
	rw_exit(&dn->dn_struct_rwlock);

	/* wait for async i/o */
	err = zio_wait(zio);
	if (err) {
		dmu_buf_rele_array(dbp, nblks, tag);
		return (err);
	}

	/* wait for other io to complete */
	if (read) {
		for (i = 0; i < nblks; i++) {
			dmu_buf_impl_t *db = (dmu_buf_impl_t *)dbp[i];
			mutex_enter(&db->db_mtx);
			while (db->db_state == DB_READ ||
			    db->db_state == DB_FILL)
				cv_wait(&db->db_changed, &db->db_mtx);
			if (db->db_state == DB_UNCACHED)
				err = SET_ERROR(EIO);
			mutex_exit(&db->db_mtx);
			if (err) {
				dmu_buf_rele_array(dbp, nblks, tag);
				return (err);
			}
		}
	}

	*numbufsp = nblks;
	*dbpp = dbp;
	return (0);
}