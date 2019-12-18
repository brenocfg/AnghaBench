#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  z_zfsvfs; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_mode; int /*<<< orphan*/  z_gid; int /*<<< orphan*/  z_uid; int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/ * lr_crtime; int /*<<< orphan*/  lr_gen; int /*<<< orphan*/  lr_mode; int /*<<< orphan*/  lr_gid; int /*<<< orphan*/  lr_uid; int /*<<< orphan*/  lr_foid; int /*<<< orphan*/  lr_doid; } ;
typedef  TYPE_2__ lr_create_t ;
struct TYPE_10__ {int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA_ZPL_CRTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ZPL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int /*<<< orphan*/  sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int /*<<< orphan*/ ,int) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_symlink(zilog_t *zilog, dmu_tx_t *tx, uint64_t txtype,
    znode_t *dzp, znode_t *zp, char *name, char *link)
{
	itx_t *itx;
	lr_create_t *lr;
	size_t namesize = strlen(name) + 1;
	size_t linksize = strlen(link) + 1;

	if (zil_replaying(zilog, tx))
		return;

	itx = zil_itx_create(txtype, sizeof (*lr) + namesize + linksize);
	lr = (lr_create_t *)&itx->itx_lr;
	lr->lr_doid = dzp->z_id;
	lr->lr_foid = zp->z_id;
	lr->lr_uid = zp->z_uid;
	lr->lr_gid = zp->z_gid;
	lr->lr_mode = zp->z_mode;
	(void) sa_lookup(zp->z_sa_hdl, SA_ZPL_GEN(zp->z_zfsvfs), &lr->lr_gen,
	    sizeof (uint64_t));
	(void) sa_lookup(zp->z_sa_hdl, SA_ZPL_CRTIME(zp->z_zfsvfs),
	    lr->lr_crtime, sizeof (uint64_t) * 2);
	bcopy(name, (char *)(lr + 1), namesize);
	bcopy(link, (char *)(lr + 1) + namesize, linksize);

	zil_itx_assign(zilog, itx, tx);
}