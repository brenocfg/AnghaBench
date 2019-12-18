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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct dbuf_hold_impl_data {int dh_depth; int /*<<< orphan*/ * dh_dr; scalar_t__ dh_err; int /*<<< orphan*/ * dh_bp; int /*<<< orphan*/ * dh_parent; int /*<<< orphan*/ * dh_db; int /*<<< orphan*/ ** dh_dbp; void* dh_tag; void* dh_fail_uncached; void* dh_fail_sparse; int /*<<< orphan*/  dh_blkid; int /*<<< orphan*/  dh_level; int /*<<< orphan*/ * dh_dn; } ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
typedef  void* boolean_t ;

/* Variables and functions */

__attribute__((used)) static void
__dbuf_hold_impl_init(struct dbuf_hold_impl_data *dh,
    dnode_t *dn, uint8_t level, uint64_t blkid,
    boolean_t fail_sparse, boolean_t fail_uncached,
    void *tag, dmu_buf_impl_t **dbp, int depth)
{
	dh->dh_dn = dn;
	dh->dh_level = level;
	dh->dh_blkid = blkid;

	dh->dh_fail_sparse = fail_sparse;
	dh->dh_fail_uncached = fail_uncached;

	dh->dh_tag = tag;
	dh->dh_dbp = dbp;

	dh->dh_db = NULL;
	dh->dh_parent = NULL;
	dh->dh_bp = NULL;
	dh->dh_err = 0;
	dh->dh_dr = NULL;

	dh->dh_depth = depth;
}