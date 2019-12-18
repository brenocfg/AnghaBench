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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SCSI_RBUF_SIZE ; 
 int /*<<< orphan*/  ata_scsi_rbuf ; 
 int /*<<< orphan*/  ata_scsi_rbuf_lock ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ata_scsi_rbuf_put(struct scsi_cmnd *cmd, bool copy_out,
				     unsigned long *flags)
{
	if (copy_out)
		sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				    ata_scsi_rbuf, ATA_SCSI_RBUF_SIZE);
	spin_unlock_irqrestore(&ata_scsi_rbuf_lock, *flags);
}