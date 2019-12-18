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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct scb {struct ahd_dma_seg* sg_list; } ;
struct ahd_softc {int flags; } ;
struct ahd_dma_seg {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct ahd_dma64_seg {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */
 int AHD_64BIT_ADDRESSING ; 
 int AHD_SG_LEN_MASK ; 
 scalar_t__ CAM_DIR_IN ; 
 int DPHASE ; 
 int /*<<< orphan*/  SCB_RESIDUAL_DATACNT ; 
 int /*<<< orphan*/  SCB_RESIDUAL_SGPTR ; 
 int /*<<< orphan*/  SCB_TASK_ATTRIBUTE ; 
 int SCB_XFERLEN_ODD ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int SG_LIST_NULL ; 
 int SG_PTR_MASK ; 
 int /*<<< orphan*/  SHADDR ; 
 int /*<<< orphan*/  ahd_get_scbptr (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inb_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inl_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inq (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_outl (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 struct ahd_dma_seg* ahd_sg_bus_to_virt (struct ahd_softc*,struct scb*,int) ; 
 int ahd_sg_virt_to_bus (struct ahd_softc*,struct scb*,struct ahd_dma_seg*) ; 
 scalar_t__ aic_get_transfer_dir (struct scb*) ; 
 int aic_le32toh (int /*<<< orphan*/ ) ; 
 int aic_le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_handle_ign_wide_residue(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	u_int scb_index;
	struct scb *scb;

	scb_index = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scb_index);
	/*
	 * XXX Actually check data direction in the sequencer?
	 * Perhaps add datadir to some spare bits in the hscb?
	 */
	if ((ahd_inb(ahd, SEQ_FLAGS) & DPHASE) == 0
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

		sgptr = ahd_inb_scbram(ahd, SCB_RESIDUAL_SGPTR);
		if ((sgptr & SG_LIST_NULL) != 0
		 && (ahd_inb_scbram(ahd, SCB_TASK_ATTRIBUTE)
		     & SCB_XFERLEN_ODD) != 0) {
			/*
			 * If the residual occurred on the last
			 * transfer and the transfer request was
			 * expected to end on an odd count, do
			 * nothing.
			 */
		} else {
			uint32_t data_cnt;
			uint64_t data_addr;
			uint32_t sglen;

			/* Pull in the rest of the sgptr */
			sgptr = ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR);
			data_cnt = ahd_inl_scbram(ahd, SCB_RESIDUAL_DATACNT);
			if ((sgptr & SG_LIST_NULL) != 0) {
				/*
				 * The residual data count is not updated
				 * for the command run to completion case.
				 * Explicitly zero the count.
				 */
				data_cnt &= ~AHD_SG_LEN_MASK;
			}
			data_addr = ahd_inq(ahd, SHADDR);
			data_cnt += 1;
			data_addr -= 1;
			sgptr &= SG_PTR_MASK;
			if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) {
				struct ahd_dma64_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

				/*
				 * The residual sg ptr points to the next S/G
				 * to load so we must go back one.
				 */
				sg--;
				sglen = aic_le32toh(sg->len) & AHD_SG_LEN_MASK;
				if (sg != scb->sg_list
				 && sglen < (data_cnt & AHD_SG_LEN_MASK)) {

					sg--;
					sglen = aic_le32toh(sg->len);
					/*
					 * Preserve High Address and SG_LIST
					 * bits while setting the count to 1.
					 */
					data_cnt = 1|(sglen&(~AHD_SG_LEN_MASK));
					data_addr = aic_le64toh(sg->addr)
						  + (sglen & AHD_SG_LEN_MASK)
						  - 1;

					/*
					 * Increment sg so it points to the
					 * "next" sg.
					 */
					sg++;
					sgptr = ahd_sg_virt_to_bus(ahd, scb,
								   sg);
				}
			} else {
				struct ahd_dma_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

				/*
				 * The residual sg ptr points to the next S/G
				 * to load so we must go back one.
				 */
				sg--;
				sglen = aic_le32toh(sg->len) & AHD_SG_LEN_MASK;
				if (sg != scb->sg_list
				 && sglen < (data_cnt & AHD_SG_LEN_MASK)) {

					sg--;
					sglen = aic_le32toh(sg->len);
					/*
					 * Preserve High Address and SG_LIST
					 * bits while setting the count to 1.
					 */
					data_cnt = 1|(sglen&(~AHD_SG_LEN_MASK));
					data_addr = aic_le32toh(sg->addr)
						  + (sglen & AHD_SG_LEN_MASK)
						  - 1;

					/*
					 * Increment sg so it points to the
					 * "next" sg.
					 */
					sg++;
					sgptr = ahd_sg_virt_to_bus(ahd, scb,
								  sg);
				}
			}
			/*
			 * Toggle the "oddness" of the transfer length
			 * to handle this mid-transfer ignore wide
			 * residue.  This ensures that the oddness is
			 * correct for subsequent data transfers.
			 */
			ahd_outb(ahd, SCB_TASK_ATTRIBUTE,
			    ahd_inb_scbram(ahd, SCB_TASK_ATTRIBUTE)
			    ^ SCB_XFERLEN_ODD);

			ahd_outl(ahd, SCB_RESIDUAL_SGPTR, sgptr);
			ahd_outl(ahd, SCB_RESIDUAL_DATACNT, data_cnt);
			/*
			 * The FIFO's pointers will be updated if/when the
			 * sequencer re-enters a data phase.
			 */
		}
	}
}