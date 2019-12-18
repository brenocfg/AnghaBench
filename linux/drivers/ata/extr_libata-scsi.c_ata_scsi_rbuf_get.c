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
 void* ata_scsi_rbuf ; 
 int /*<<< orphan*/  ata_scsi_rbuf_lock ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void *ata_scsi_rbuf_get(struct scsi_cmnd *cmd, bool copy_in,
			       unsigned long *flags)
{
	spin_lock_irqsave(&ata_scsi_rbuf_lock, *flags);

	memset(ata_scsi_rbuf, 0, ATA_SCSI_RBUF_SIZE);
	if (copy_in)
		sg_copy_to_buffer(scsi_sglist(cmd), scsi_sg_count(cmd),
				  ata_scsi_rbuf, ATA_SCSI_RBUF_SIZE);
	return ata_scsi_rbuf;
}