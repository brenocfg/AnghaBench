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
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_DNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_assign_arcbuf_dnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
dmu_assign_arcbuf(dmu_buf_t *handle, uint64_t offset, arc_buf_t *buf,
    dmu_tx_t *tx)
{
	dmu_buf_impl_t *dbuf = (dmu_buf_impl_t *)handle;

	DB_DNODE_ENTER(dbuf);
	dmu_assign_arcbuf_dnode(DB_DNODE(dbuf), offset, buf, tx);
	DB_DNODE_EXIT(dbuf);
}