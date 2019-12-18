#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kern_data_ptr; } ;
union ctl_io {TYPE_1__ scsiio; } ;
struct scsi_get_lba_status_data {TYPE_3__* descr; } ;
struct ctl_lba_len_flags {scalar_t__ lba; } ;
struct TYPE_7__ {int blocksize; } ;
struct ctl_be_block_lun {int size_bytes; TYPE_2__ cbe_lun; int /*<<< orphan*/  vn; } ;
struct ctl_be_block_io {union ctl_io* io; } ;
typedef  int off_t ;
struct TYPE_9__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_8__ {int status; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 struct ctl_lba_len_flags* ARGS (union ctl_io*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  FIOSEEKDATA ; 
 int /*<<< orphan*/  FIOSEEKHOLE ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int VOP_IOCTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_complete_beio (struct ctl_be_block_io*) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  scsi_u64to8b (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ctl_be_block_gls_file(struct ctl_be_block_lun *be_lun,
			struct ctl_be_block_io *beio)
{
	union ctl_io *io = beio->io;
	struct ctl_lba_len_flags *lbalen = ARGS(io);
	struct scsi_get_lba_status_data *data;
	off_t roff, off;
	int error, status;

	DPRINTF("entered\n");

	off = roff = ((off_t)lbalen->lba) * be_lun->cbe_lun.blocksize;
	vn_lock(be_lun->vn, LK_SHARED | LK_RETRY);
	error = VOP_IOCTL(be_lun->vn, FIOSEEKHOLE, &off,
	    0, curthread->td_ucred, curthread);
	if (error == 0 && off > roff)
		status = 0;	/* mapped up to off */
	else {
		error = VOP_IOCTL(be_lun->vn, FIOSEEKDATA, &off,
		    0, curthread->td_ucred, curthread);
		if (error == 0 && off > roff)
			status = 1;	/* deallocated up to off */
		else {
			status = 0;	/* unknown up to the end */
			off = be_lun->size_bytes;
		}
	}
	VOP_UNLOCK(be_lun->vn, 0);

	data = (struct scsi_get_lba_status_data *)io->scsiio.kern_data_ptr;
	scsi_u64to8b(lbalen->lba, data->descr[0].addr);
	scsi_ulto4b(MIN(UINT32_MAX, off / be_lun->cbe_lun.blocksize -
	    lbalen->lba), data->descr[0].length);
	data->descr[0].status = status;

	ctl_complete_beio(beio);
}