#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kern_data_ptr; } ;
union ctl_io {TYPE_1__ scsiio; } ;
struct scsi_get_lba_status_data {TYPE_3__* descr; } ;
struct ctl_lba_len_flags {scalar_t__ lba; } ;
struct TYPE_5__ {int blocksize; } ;
struct ctl_be_block_lun {int size_bytes; TYPE_2__ cbe_lun; int /*<<< orphan*/  vn; } ;
struct ctl_be_block_io {union ctl_io* io; } ;
struct cdevsw {int (* d_ioctl ) (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct cdev {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int status; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 struct ctl_lba_len_flags* ARGS (union ctl_io*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  FIOSEEKDATA ; 
 int /*<<< orphan*/  FIOSEEKHOLE ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ctl_complete_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 struct cdevsw* devvn_refthread (int /*<<< orphan*/ ,struct cdev**,int*) ; 
 int /*<<< orphan*/  scsi_u64to8b (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_be_block_gls_zvol(struct ctl_be_block_lun *be_lun,
			struct ctl_be_block_io *beio)
{
	union ctl_io *io = beio->io;
	struct cdevsw *csw;
	struct cdev *dev;
	struct ctl_lba_len_flags *lbalen = ARGS(io);
	struct scsi_get_lba_status_data *data;
	off_t roff, off;
	int error, ref, status;

	DPRINTF("entered\n");

	csw = devvn_refthread(be_lun->vn, &dev, &ref);
	if (csw == NULL) {
		status = 0;	/* unknown up to the end */
		off = be_lun->size_bytes;
		goto done;
	}
	off = roff = ((off_t)lbalen->lba) * be_lun->cbe_lun.blocksize;
	error = csw->d_ioctl(dev, FIOSEEKHOLE, (caddr_t)&off, FREAD,
	    curthread);
	if (error == 0 && off > roff)
		status = 0;	/* mapped up to off */
	else {
		error = csw->d_ioctl(dev, FIOSEEKDATA, (caddr_t)&off, FREAD,
		    curthread);
		if (error == 0 && off > roff)
			status = 1;	/* deallocated up to off */
		else {
			status = 0;	/* unknown up to the end */
			off = be_lun->size_bytes;
		}
	}
	dev_relthread(dev, ref);

done:
	data = (struct scsi_get_lba_status_data *)io->scsiio.kern_data_ptr;
	scsi_u64to8b(lbalen->lba, data->descr[0].addr);
	scsi_ulto4b(MIN(UINT32_MAX, off / be_lun->cbe_lun.blocksize -
	    lbalen->lba), data->descr[0].length);
	data->descr[0].status = status;

	ctl_complete_beio(beio);
}