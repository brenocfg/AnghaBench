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
union ctl_io {int /*<<< orphan*/  scsiio; } ;
struct mount {int dummy; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  io_lock; TYPE_2__* vn; } ;
struct ctl_be_block_io {int /*<<< orphan*/  ds_t0; int /*<<< orphan*/  ds_trans_type; int /*<<< orphan*/  ds_tag_type; int /*<<< orphan*/  io_len; TYPE_1__* lun; scalar_t__ io_arg; union ctl_io* io; } ;
struct TYPE_7__ {struct mount* v_mount; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 scalar_t__ MNT_SHARED_WRITES (struct mount*) ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int VOP_FSYNC (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_complete_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  ctl_set_internal_failure (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ctl_set_success (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  devstat_end_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vn_start_write (TYPE_2__*,struct mount**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_be_block_flush_file(struct ctl_be_block_lun *be_lun,
			struct ctl_be_block_io *beio)
{
	union ctl_io *io = beio->io;
	struct mount *mountpoint;
	int error, lock_flags;

	DPRINTF("entered\n");

	binuptime(&beio->ds_t0);
	mtx_lock(&be_lun->io_lock);
	devstat_start_transaction(beio->lun->disk_stats, &beio->ds_t0);
	mtx_unlock(&be_lun->io_lock);

	(void) vn_start_write(be_lun->vn, &mountpoint, V_WAIT);

	if (MNT_SHARED_WRITES(mountpoint) ||
	    ((mountpoint == NULL) && MNT_SHARED_WRITES(be_lun->vn->v_mount)))
		lock_flags = LK_SHARED;
	else
		lock_flags = LK_EXCLUSIVE;
	vn_lock(be_lun->vn, lock_flags | LK_RETRY);
	error = VOP_FSYNC(be_lun->vn, beio->io_arg ? MNT_NOWAIT : MNT_WAIT,
	    curthread);
	VOP_UNLOCK(be_lun->vn, 0);

	vn_finished_write(mountpoint);

	mtx_lock(&be_lun->io_lock);
	devstat_end_transaction(beio->lun->disk_stats, beio->io_len,
	    beio->ds_tag_type, beio->ds_trans_type,
	    /*now*/ NULL, /*then*/&beio->ds_t0);
	mtx_unlock(&be_lun->io_lock);

	if (error == 0)
		ctl_set_success(&io->scsiio);
	else {
		/* XXX KDM is there is a better error here? */
		ctl_set_internal_failure(&io->scsiio,
					 /*sks_valid*/ 1,
					 /*retry_count*/ 0xbad1);
	}

	ctl_complete_beio(beio);
}