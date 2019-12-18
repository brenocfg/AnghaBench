#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int done; } ;
union cvmx_mio_boot_dma_intx {scalar_t__ u64; TYPE_3__ s; } ;
struct TYPE_7__ {int size; } ;
union cvmx_mio_boot_dma_cfgx {scalar_t__ u64; TYPE_2__ s; } ;
typedef  int /*<<< orphan*/  u8 ;
struct octeon_cf_port {scalar_t__ dma_base; } ;
struct TYPE_10__ {scalar_t__ protocol; } ;
struct ata_queued_cmd {TYPE_5__ tf; int /*<<< orphan*/  err_mask; } ;
struct ata_eh_info {int dummy; } ;
struct TYPE_6__ {struct ata_eh_info eh_info; } ;
struct ata_port {scalar_t__ hsm_task_state; TYPE_4__* ops; int /*<<< orphan*/  print_id; struct octeon_cf_port* private_data; TYPE_1__ link; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* sff_check_status ) (struct ata_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_HOST_BUS ; 
 scalar_t__ ATA_PROT_DMA ; 
 scalar_t__ DMA_CFG ; 
 scalar_t__ DMA_INT ; 
 scalar_t__ DMA_INT_EN ; 
 scalar_t__ HSM_ST_ERR ; 
 scalar_t__ HSM_ST_LAST ; 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_hsm_move (struct ata_port*,struct ata_queued_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int octeon_cf_dma_finished(struct ata_port *ap,
					struct ata_queued_cmd *qc)
{
	struct ata_eh_info *ehi = &ap->link.eh_info;
	struct octeon_cf_port *cf_port = ap->private_data;
	union cvmx_mio_boot_dma_cfgx dma_cfg;
	union cvmx_mio_boot_dma_intx dma_int;
	u8 status;

	VPRINTK("ata%u: protocol %d task_state %d\n",
		ap->print_id, qc->tf.protocol, ap->hsm_task_state);


	if (ap->hsm_task_state != HSM_ST_LAST)
		return 0;

	dma_cfg.u64 = cvmx_read_csr(cf_port->dma_base + DMA_CFG);
	if (dma_cfg.s.size != 0xfffff) {
		/* Error, the transfer was not complete.  */
		qc->err_mask |= AC_ERR_HOST_BUS;
		ap->hsm_task_state = HSM_ST_ERR;
	}

	/* Stop and clear the dma engine.  */
	dma_cfg.u64 = 0;
	dma_cfg.s.size = -1;
	cvmx_write_csr(cf_port->dma_base + DMA_CFG, dma_cfg.u64);

	/* Disable the interrupt.  */
	dma_int.u64 = 0;
	cvmx_write_csr(cf_port->dma_base + DMA_INT_EN, dma_int.u64);

	/* Clear the DMA complete status */
	dma_int.s.done = 1;
	cvmx_write_csr(cf_port->dma_base + DMA_INT, dma_int.u64);

	status = ap->ops->sff_check_status(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	if (unlikely(qc->err_mask) && (qc->tf.protocol == ATA_PROT_DMA))
		ata_ehi_push_desc(ehi, "DMA stat 0x%x", status);

	return 1;
}