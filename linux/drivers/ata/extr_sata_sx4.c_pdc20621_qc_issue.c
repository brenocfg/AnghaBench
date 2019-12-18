#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int protocol; int flags; } ;
struct ata_queued_cmd {TYPE_1__ tf; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 130 
#define  ATA_PROT_DMA 129 
#define  ATA_PROT_NODATA 128 
 int ATA_TFLAG_POLLING ; 
 int /*<<< orphan*/  BUG () ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pdc20621_packet_start (struct ata_queued_cmd*) ; 

__attribute__((used)) static unsigned int pdc20621_qc_issue(struct ata_queued_cmd *qc)
{
	switch (qc->tf.protocol) {
	case ATA_PROT_NODATA:
		if (qc->tf.flags & ATA_TFLAG_POLLING)
			break;
		/*FALLTHROUGH*/
	case ATA_PROT_DMA:
		pdc20621_packet_start(qc);
		return 0;

	case ATAPI_PROT_DMA:
		BUG();
		break;

	default:
		break;
	}

	return ata_sff_qc_issue(qc);
}