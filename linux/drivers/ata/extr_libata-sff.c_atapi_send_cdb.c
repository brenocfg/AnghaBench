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
struct TYPE_4__ {int protocol; } ;
struct ata_queued_cmd {TYPE_1__ tf; TYPE_2__* dev; int /*<<< orphan*/  cdb; } ;
struct ata_port {TYPE_3__* ops; void* hsm_task_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bmdma_start ) (struct ata_queued_cmd*) ;int /*<<< orphan*/  (* sff_data_xfer ) (struct ata_queued_cmd*,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_5__ {int cdb_len; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 130 
#define  ATAPI_PROT_NODATA 129 
#define  ATAPI_PROT_PIO 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 void* HSM_ST ; 
 void* HSM_ST_LAST ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ata_sff_sync (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_queued_cmd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ata_queued_cmd*) ; 

__attribute__((used)) static void atapi_send_cdb(struct ata_port *ap, struct ata_queued_cmd *qc)
{
	/* send SCSI cdb */
	DPRINTK("send cdb\n");
	WARN_ON_ONCE(qc->dev->cdb_len < 12);

	ap->ops->sff_data_xfer(qc, qc->cdb, qc->dev->cdb_len, 1);
	ata_sff_sync(ap);
	/* FIXME: If the CDB is for DMA do we need to do the transition delay
	   or is bmdma_start guaranteed to do it ? */
	switch (qc->tf.protocol) {
	case ATAPI_PROT_PIO:
		ap->hsm_task_state = HSM_ST;
		break;
	case ATAPI_PROT_NODATA:
		ap->hsm_task_state = HSM_ST_LAST;
		break;
#ifdef CONFIG_ATA_BMDMA
	case ATAPI_PROT_DMA:
		ap->hsm_task_state = HSM_ST_LAST;
		/* initiate bmdma */
		ap->ops->bmdma_start(qc);
		break;
#endif /* CONFIG_ATA_BMDMA */
	default:
		BUG();
	}
}