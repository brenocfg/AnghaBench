#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ dn_bonuslen; } ;
typedef  TYPE_5__ dnode_t ;
struct TYPE_21__ {scalar_t__ tx_txg; } ;
typedef  TYPE_6__ dmu_tx_t ;
struct TYPE_16__ {void* db_data; } ;
struct TYPE_22__ {scalar_t__ db_dirtycnt; TYPE_8__* db_last_dirty; TYPE_1__ db; } ;
typedef  TYPE_7__ dmu_buf_impl_t ;
struct TYPE_18__ {TYPE_2__* dr_data; } ;
struct TYPE_19__ {TYPE_3__ dl; } ;
struct TYPE_23__ {scalar_t__ dr_txg; TYPE_11__* dr_dbuf; TYPE_4__ dt; struct TYPE_23__* dr_next; } ;
typedef  TYPE_8__ dbuf_dirty_record_t ;
struct TYPE_17__ {void* b_data; } ;
struct TYPE_15__ {scalar_t__ db_blkid; } ;

/* Variables and functions */
 TYPE_5__* DB_DNODE (TYPE_11__*) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (TYPE_11__*) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (TYPE_11__*) ; 
 scalar_t__ DMU_SPILL_BLKID ; 

__attribute__((used)) static void *
dmu_objset_userquota_find_data(dmu_buf_impl_t *db, dmu_tx_t *tx)
{
	dbuf_dirty_record_t *dr, **drp;
	void *data;

	if (db->db_dirtycnt == 0)
		return (db->db.db_data);  /* Nothing is changing */

	for (drp = &db->db_last_dirty; (dr = *drp) != NULL; drp = &dr->dr_next)
		if (dr->dr_txg == tx->tx_txg)
			break;

	if (dr == NULL) {
		data = NULL;
	} else {
		dnode_t *dn;

		DB_DNODE_ENTER(dr->dr_dbuf);
		dn = DB_DNODE(dr->dr_dbuf);

		if (dn->dn_bonuslen == 0 &&
		    dr->dr_dbuf->db_blkid == DMU_SPILL_BLKID)
			data = dr->dt.dl.dr_data->b_data;
		else
			data = dr->dt.dl.dr_data;

		DB_DNODE_EXIT(dr->dr_dbuf);
	}

	return (data);
}