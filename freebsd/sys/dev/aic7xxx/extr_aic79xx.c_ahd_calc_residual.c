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
typedef  int uint32_t ;
struct scb {int flags; struct hardware_scb* hscb; } ;
struct initiator_status {int /*<<< orphan*/  residual_datacnt; int /*<<< orphan*/  residual_sgptr; } ;
struct TYPE_2__ {struct initiator_status istatus; } ;
struct hardware_scb {TYPE_1__ shared_data; int /*<<< orphan*/  sgptr; } ;
struct ahd_softc {int dummy; } ;
struct ahd_dma_seg {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int AHD_DMA_LAST_SEG ; 
 int AHD_SG_LEN_MASK ; 
 int AHD_SHOW_MISC ; 
 int /*<<< orphan*/  CAM_DATA_RUN_ERR ; 
 int SCB_GET_TAG (struct scb*) ; 
 int SCB_SENSE ; 
 int SG_FULL_RESID ; 
 int SG_LIST_NULL ; 
 int SG_OVERRUN_RESID ; 
 int SG_PTR_MASK ; 
 int SG_STATUS_VALID ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_freeze_devq (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 struct ahd_dma_seg* ahd_sg_bus_to_virt (struct ahd_softc*,struct scb*,int) ; 
 int /*<<< orphan*/  aic_freeze_scb (struct scb*) ; 
 int aic_get_transfer_length (struct scb*) ; 
 int aic_le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_set_residual (struct scb*,int) ; 
 int /*<<< orphan*/  aic_set_sense_residual (struct scb*,int) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ahd_calc_residual(struct ahd_softc *ahd, struct scb *scb)
{
	struct hardware_scb *hscb;
	struct initiator_status *spkt;
	uint32_t sgptr;
	uint32_t resid_sgptr;
	uint32_t resid;

	/*
	 * 5 cases.
	 * 1) No residual.
	 *    SG_STATUS_VALID clear in sgptr.
	 * 2) Transferless command
	 * 3) Never performed any transfers.
	 *    sgptr has SG_FULL_RESID set.
	 * 4) No residual but target did not
	 *    save data pointers after the
	 *    last transfer, so sgptr was
	 *    never updated.
	 * 5) We have a partial residual.
	 *    Use residual_sgptr to determine
	 *    where we are.
	 */

	hscb = scb->hscb;
	sgptr = aic_le32toh(hscb->sgptr);
	if ((sgptr & SG_STATUS_VALID) == 0)
		/* Case 1 */
		return;
	sgptr &= ~SG_STATUS_VALID;

	if ((sgptr & SG_LIST_NULL) != 0)
		/* Case 2 */
		return;

	/*
	 * Residual fields are the same in both
	 * target and initiator status packets,
	 * so we can always use the initiator fields
	 * regardless of the role for this SCB.
	 */
	spkt = &hscb->shared_data.istatus;
	resid_sgptr = aic_le32toh(spkt->residual_sgptr);
	if ((sgptr & SG_FULL_RESID) != 0) {
		/* Case 3 */
		resid = aic_get_transfer_length(scb);
	} else if ((resid_sgptr & SG_LIST_NULL) != 0) {
		/* Case 4 */
		return;
	} else if ((resid_sgptr & SG_OVERRUN_RESID) != 0) {
		ahd_print_path(ahd, scb);
		printf("data overrun detected Tag == 0x%x.\n",
		       SCB_GET_TAG(scb));
		ahd_freeze_devq(ahd, scb);
		aic_set_transaction_status(scb, CAM_DATA_RUN_ERR);
		aic_freeze_scb(scb);
		return;
	} else if ((resid_sgptr & ~SG_PTR_MASK) != 0) {
		panic("Bogus resid sgptr value 0x%x\n", resid_sgptr);
		/* NOTREACHED */
	} else {
		struct ahd_dma_seg *sg;

		/*
		 * Remainder of the SG where the transfer
		 * stopped.  
		 */
		resid = aic_le32toh(spkt->residual_datacnt) & AHD_SG_LEN_MASK;
		sg = ahd_sg_bus_to_virt(ahd, scb, resid_sgptr & SG_PTR_MASK);

		/* The residual sg_ptr always points to the next sg */
		sg--;

		/*
		 * Add up the contents of all residual
		 * SG segments that are after the SG where
		 * the transfer stopped.
		 */
		while ((aic_le32toh(sg->len) & AHD_DMA_LAST_SEG) == 0) {
			sg++;
			resid += aic_le32toh(sg->len) & AHD_SG_LEN_MASK;
		}
	}
	if ((scb->flags & SCB_SENSE) == 0)
		aic_set_residual(scb, resid);
	else
		aic_set_sense_residual(scb, resid);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0) {
		ahd_print_path(ahd, scb);
		printf("Handled %sResidual of %d bytes\n",
		       (scb->flags & SCB_SENSE) ? "Sense " : "", resid);
	}
#endif
}