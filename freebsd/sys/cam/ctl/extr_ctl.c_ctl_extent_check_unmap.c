#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ io_type; int flags; int /*<<< orphan*/ * ctl_private; } ;
struct TYPE_3__ {scalar_t__* cdb; } ;
union ctl_io {TYPE_2__ io_hdr; TYPE_1__ scsiio; } ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_unmap_desc {int /*<<< orphan*/  length; int /*<<< orphan*/  lba; } ;
struct ctl_ptr_len_flags {int len; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int CTL_ACTION_BLOCK ; 
 int CTL_ACTION_ERROR ; 
 int CTL_ACTION_PASS ; 
 int CTL_FLAG_ALLOCATED ; 
 scalar_t__ CTL_IO_SCSI ; 
 size_t CTL_PRIV_LBA_LEN ; 
 scalar_t__ UNMAP ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_extent_check_unmap(union ctl_io *io, uint64_t lba2, uint64_t len2)
{
	struct ctl_ptr_len_flags *ptrlen;
	struct scsi_unmap_desc *buf, *end, *range;
	uint64_t lba;
	uint32_t len;

	/* If not UNMAP -- go other way. */
	if (io->io_hdr.io_type != CTL_IO_SCSI ||
	    io->scsiio.cdb[0] != UNMAP)
		return (CTL_ACTION_ERROR);

	/* If UNMAP without data -- block and wait for data. */
	ptrlen = (struct ctl_ptr_len_flags *)
	    &io->io_hdr.ctl_private[CTL_PRIV_LBA_LEN];
	if ((io->io_hdr.flags & CTL_FLAG_ALLOCATED) == 0 ||
	    ptrlen->ptr == NULL)
		return (CTL_ACTION_BLOCK);

	/* UNMAP with data -- check for collision. */
	buf = (struct scsi_unmap_desc *)ptrlen->ptr;
	end = buf + ptrlen->len / sizeof(*buf);
	for (range = buf; range < end; range++) {
		lba = scsi_8btou64(range->lba);
		len = scsi_4btoul(range->length);
		if ((lba < lba2 + len2) && (lba + len > lba2))
			return (CTL_ACTION_BLOCK);
	}
	return (CTL_ACTION_PASS);
}