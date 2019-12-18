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
union ctl_io {int /*<<< orphan*/  scsiio; } ;
struct scsi_unmap_desc {int /*<<< orphan*/  length; int /*<<< orphan*/  lba; } ;
struct ctl_ptr_len_flags {int flags; int len; scalar_t__ ptr; } ;
struct ctl_be_lun {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARGS (union ctl_io*) ; 
 struct ctl_be_lun* CTL_BACKEND_LUN (union ctl_io*) ; 
 int SU_ANCHOR ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_delete (struct ctl_be_lun*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_8btou64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_unmap(union ctl_io *io)
{
	struct ctl_be_lun *cbe_lun = CTL_BACKEND_LUN(io);
	struct ctl_ptr_len_flags *ptrlen = (struct ctl_ptr_len_flags *)ARGS(io);
	struct scsi_unmap_desc *buf, *end;

	if ((ptrlen->flags & ~SU_ANCHOR) != 0) {
		ctl_set_invalid_field(&io->scsiio,
				      /*sks_valid*/ 0,
				      /*command*/ 0,
				      /*field*/ 0,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_config_write_done(io);
		return;
	}

	buf = (struct scsi_unmap_desc *)ptrlen->ptr;
	end = buf + ptrlen->len / sizeof(*buf);
	for (; buf < end; buf++) {
		ctl_backend_ramdisk_delete(cbe_lun,
		    scsi_8btou64(buf->lba), scsi_4btoul(buf->length),
		    (ptrlen->flags & SU_ANCHOR) != 0);
	}

	ctl_set_success(&io->scsiio);
	ctl_config_write_done(io);
}