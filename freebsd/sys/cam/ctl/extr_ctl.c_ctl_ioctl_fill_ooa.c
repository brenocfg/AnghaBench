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
struct TYPE_4__ {int flags; int /*<<< orphan*/ * blocker; int /*<<< orphan*/  start_bt; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  cdb; int /*<<< orphan*/  tag_num; } ;
union ctl_io {TYPE_2__ io_hdr; TYPE_1__ scsiio; } ;
typedef  scalar_t__ uint32_t ;
struct ctl_ooa_entry {int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  cdb; int /*<<< orphan*/  start_bt; int /*<<< orphan*/  lun_num; int /*<<< orphan*/  tag_num; } ;
struct ctl_ooa {scalar_t__ alloc_num; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  lun; int /*<<< orphan*/  ooa_queue; } ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_DMA_INPROG ; 
 int CTL_FLAG_DMA_QUEUED ; 
 int CTL_FLAG_IS_WAS_ON_RTR ; 
 int /*<<< orphan*/  CTL_OOACMD_FLAG_ABORT ; 
 int /*<<< orphan*/  CTL_OOACMD_FLAG_BLOCKED ; 
 int /*<<< orphan*/  CTL_OOACMD_FLAG_DMA ; 
 int /*<<< orphan*/  CTL_OOACMD_FLAG_DMA_QUEUED ; 
 int /*<<< orphan*/  CTL_OOACMD_FLAG_RTR ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ooa_links ; 

__attribute__((used)) static void
ctl_ioctl_fill_ooa(struct ctl_lun *lun, uint32_t *cur_fill_num,
		   struct ctl_ooa *ooa_hdr, struct ctl_ooa_entry *kern_entries)
{
	union ctl_io *io;

	mtx_lock(&lun->lun_lock);
	for (io = (union ctl_io *)TAILQ_FIRST(&lun->ooa_queue); (io != NULL);
	     (*cur_fill_num)++, io = (union ctl_io *)TAILQ_NEXT(&io->io_hdr,
	     ooa_links)) {
		struct ctl_ooa_entry *entry;

		/*
		 * If we've got more than we can fit, just count the
		 * remaining entries.
		 */
		if (*cur_fill_num >= ooa_hdr->alloc_num)
			continue;

		entry = &kern_entries[*cur_fill_num];

		entry->tag_num = io->scsiio.tag_num;
		entry->lun_num = lun->lun;
#ifdef CTL_TIME_IO
		entry->start_bt = io->io_hdr.start_bt;
#endif
		bcopy(io->scsiio.cdb, entry->cdb, io->scsiio.cdb_len);
		entry->cdb_len = io->scsiio.cdb_len;
		if (io->io_hdr.blocker != NULL)
			entry->cmd_flags |= CTL_OOACMD_FLAG_BLOCKED;

		if (io->io_hdr.flags & CTL_FLAG_DMA_INPROG)
			entry->cmd_flags |= CTL_OOACMD_FLAG_DMA;

		if (io->io_hdr.flags & CTL_FLAG_ABORT)
			entry->cmd_flags |= CTL_OOACMD_FLAG_ABORT;

		if (io->io_hdr.flags & CTL_FLAG_IS_WAS_ON_RTR)
			entry->cmd_flags |= CTL_OOACMD_FLAG_RTR;

		if (io->io_hdr.flags & CTL_FLAG_DMA_QUEUED)
			entry->cmd_flags |= CTL_OOACMD_FLAG_DMA_QUEUED;
	}
	mtx_unlock(&lun->lun_lock);
}