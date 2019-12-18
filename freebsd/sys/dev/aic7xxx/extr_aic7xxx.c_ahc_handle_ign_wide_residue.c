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
typedef  int uint32_t ;
typedef  int u_int ;
struct scb {struct ahc_dma_seg* sg_list; } ;
struct ahc_softc {int dummy; } ;
struct ahc_dma_seg {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct ahc_devinfo {int dummy; } ;

/* Variables and functions */
 int AHC_SG_LEN_MASK ; 
 scalar_t__ CAM_DIR_IN ; 
 int DPHASE ; 
 int /*<<< orphan*/  SCB_LUN ; 
 int /*<<< orphan*/  SCB_RESIDUAL_DATACNT ; 
 int /*<<< orphan*/  SCB_RESIDUAL_SGPTR ; 
 int /*<<< orphan*/  SCB_TAG ; 
 int SCB_XFERLEN_ODD ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int SG_LIST_NULL ; 
 int SG_PTR_MASK ; 
 int /*<<< orphan*/  SHADDR ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int ahc_inl (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 struct scb* ahc_lookup_scb (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_outl (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 struct ahc_dma_seg* ahc_sg_bus_to_virt (struct scb*,int) ; 
 int ahc_sg_virt_to_bus (struct scb*,struct ahc_dma_seg*) ; 
 scalar_t__ aic_get_transfer_dir (struct scb*) ; 
 int aic_le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_handle_ign_wide_residue(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{
	u_int scb_index;
	struct scb *scb;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	/*
	 * XXX Actually check data direction in the sequencer?
	 * Perhaps add datadir to some spare bits in the hscb?
	 */
	if ((ahc_inb(ahc, SEQ_FLAGS) & DPHASE) == 0
	 || aic_get_transfer_dir(scb) != CAM_DIR_IN) {
		/*
		 * Ignore the message if we haven't
		 * seen an appropriate data phase yet.
		 */
	} else {
		/*
		 * If the residual occurred on the last
		 * transfer and the transfer request was
		 * expected to end on an odd count, do
		 * nothing.  Otherwise, subtract a byte
		 * and update the residual count accordingly.
		 */
		uint32_t sgptr;

		sgptr = ahc_inb(ahc, SCB_RESIDUAL_SGPTR);
		if ((sgptr & SG_LIST_NULL) != 0
		 && (ahc_inb(ahc, SCB_LUN) & SCB_XFERLEN_ODD) != 0) {
			/*
			 * If the residual occurred on the last
			 * transfer and the transfer request was
			 * expected to end on an odd count, do
			 * nothing.
			 */
		} else {
			struct ahc_dma_seg *sg;
			uint32_t data_cnt;
			uint32_t data_addr;
			uint32_t sglen;

			/* Pull in all of the sgptr */
			sgptr = ahc_inl(ahc, SCB_RESIDUAL_SGPTR);
			data_cnt = ahc_inl(ahc, SCB_RESIDUAL_DATACNT);

			if ((sgptr & SG_LIST_NULL) != 0) {
				/*
				 * The residual data count is not updated
				 * for the command run to completion case.
				 * Explicitly zero the count.
				 */
				data_cnt &= ~AHC_SG_LEN_MASK;
			}

			data_addr = ahc_inl(ahc, SHADDR);

			data_cnt += 1;
			data_addr -= 1;
			sgptr &= SG_PTR_MASK;

			sg = ahc_sg_bus_to_virt(scb, sgptr);

			/*
			 * The residual sg ptr points to the next S/G
			 * to load so we must go back one.
			 */
			sg--;
			sglen = aic_le32toh(sg->len) & AHC_SG_LEN_MASK;
			if (sg != scb->sg_list
			 && sglen < (data_cnt & AHC_SG_LEN_MASK)) {

				sg--;
				sglen = aic_le32toh(sg->len);
				/*
				 * Preserve High Address and SG_LIST bits
				 * while setting the count to 1.
				 */
				data_cnt = 1 | (sglen & (~AHC_SG_LEN_MASK));
				data_addr = aic_le32toh(sg->addr)
					  + (sglen & AHC_SG_LEN_MASK) - 1;

				/*
				 * Increment sg so it points to the
				 * "next" sg.
				 */
				sg++;
				sgptr = ahc_sg_virt_to_bus(scb, sg);
			}
			ahc_outl(ahc, SCB_RESIDUAL_SGPTR, sgptr);
			ahc_outl(ahc, SCB_RESIDUAL_DATACNT, data_cnt);
			/*
			 * Toggle the "oddness" of the transfer length
			 * to handle this mid-transfer ignore wide
			 * residue.  This ensures that the oddness is
			 * correct for subsequent data transfers.
			 */
			ahc_outb(ahc, SCB_LUN,
				 ahc_inb(ahc, SCB_LUN) ^ SCB_XFERLEN_ODD);
		}
	}
}