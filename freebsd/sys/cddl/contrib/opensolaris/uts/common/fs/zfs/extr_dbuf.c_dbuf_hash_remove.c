#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  db_object; } ;
struct TYPE_8__ {scalar_t__ db_state; struct TYPE_8__* db_hash_next; int /*<<< orphan*/  db_mtx; int /*<<< orphan*/  db_holds; int /*<<< orphan*/  db_blkid; int /*<<< orphan*/  db_level; TYPE_1__ db; int /*<<< orphan*/  db_objset; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;
struct TYPE_9__ {size_t hash_table_mask; TYPE_2__** hash_table; } ;
typedef  TYPE_3__ dbuf_hash_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBUF_HASH_MUTEX (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  DBUF_STAT_BUMPDOWN (int /*<<< orphan*/ ) ; 
 scalar_t__ DB_EVICTING ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_64 (int /*<<< orphan*/ *) ; 
 size_t dbuf_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbuf_hash_count ; 
 TYPE_3__ dbuf_hash_table ; 
 int /*<<< orphan*/  hash_chains ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ ) ; 
 int zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_hash_remove(dmu_buf_impl_t *db)
{
	dbuf_hash_table_t *h = &dbuf_hash_table;
	uint64_t hv, idx;
	dmu_buf_impl_t *dbf, **dbp;

	hv = dbuf_hash(db->db_objset, db->db.db_object,
	    db->db_level, db->db_blkid);
	idx = hv & h->hash_table_mask;

	/*
	 * We mustn't hold db_mtx to maintain lock ordering:
	 * DBUF_HASH_MUTEX > db_mtx.
	 */
	ASSERT(zfs_refcount_is_zero(&db->db_holds));
	ASSERT(db->db_state == DB_EVICTING);
	ASSERT(!MUTEX_HELD(&db->db_mtx));

	mutex_enter(DBUF_HASH_MUTEX(h, idx));
	dbp = &h->hash_table[idx];
	while ((dbf = *dbp) != db) {
		dbp = &dbf->db_hash_next;
		ASSERT(dbf != NULL);
	}
	*dbp = db->db_hash_next;
	db->db_hash_next = NULL;
	if (h->hash_table[idx] &&
	    h->hash_table[idx]->db_hash_next == NULL)
		DBUF_STAT_BUMPDOWN(hash_chains);
	mutex_exit(DBUF_HASH_MUTEX(h, idx));
	atomic_dec_64(&dbuf_hash_count);
}