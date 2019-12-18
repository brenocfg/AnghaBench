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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * ctl_private; int /*<<< orphan*/  status; } ;
struct ctl_scsiio {TYPE_1__ io_hdr; } ;
union ctl_io {struct ctl_scsiio scsiio; } ;
struct ctl_lun {TYPE_3__* backend; TYPE_2__* be_lun; } ;
struct ctl_lba_len_flags {scalar_t__ lba; scalar_t__ len; } ;
struct TYPE_6__ {int (* config_write ) (union ctl_io*) ;} ;
struct TYPE_5__ {scalar_t__ maxlba; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_IO_CONT ; 
 struct ctl_lun* CTL_LUN (union ctl_io*) ; 
 size_t CTL_PRIV_LBA_LEN ; 
 int /*<<< orphan*/  CTL_STATUS_NONE ; 
 scalar_t__ UINT32_MAX ; 
 int stub1 (union ctl_io*) ; 

__attribute__((used)) static int
ctl_write_same_cont(union ctl_io *io)
{
	struct ctl_lun *lun = CTL_LUN(io);
	struct ctl_scsiio *ctsio;
	struct ctl_lba_len_flags *lbalen;
	int retval;

	ctsio = &io->scsiio;
	ctsio->io_hdr.status = CTL_STATUS_NONE;
	lbalen = (struct ctl_lba_len_flags *)
	    &ctsio->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	lbalen->lba += lbalen->len;
	if ((lun->be_lun->maxlba + 1) - lbalen->lba <= UINT32_MAX) {
		ctsio->io_hdr.flags &= ~CTL_FLAG_IO_CONT;
		lbalen->len = (lun->be_lun->maxlba + 1) - lbalen->lba;
	}

	CTL_DEBUG_PRINT(("ctl_write_same_cont: calling config_write()\n"));
	retval = lun->backend->config_write((union ctl_io *)ctsio);
	return (retval);
}