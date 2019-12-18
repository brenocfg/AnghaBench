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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvme_controller {int quirks; } ;

/* Variables and functions */
 int B4_CHK_RDY_DELAY_MS ; 
 int NVME_CC_REG_EN_MASK ; 
 int NVME_CC_REG_EN_SHIFT ; 
 int NVME_CSTS_REG_RDY_MASK ; 
 int NVME_CSTS_REG_RDY_SHIFT ; 
 int QUIRK_DELAY_B4_CHK_RDY ; 
 int hz ; 
 int nvme_ctrlr_wait_for_ready (struct nvme_controller*,int) ; 
 int nvme_mmio_read_4 (struct nvme_controller*,int) ; 
 int /*<<< orphan*/  nvme_mmio_write_4 (struct nvme_controller*,int,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static int
nvme_ctrlr_disable(struct nvme_controller *ctrlr)
{
	uint32_t cc;
	uint32_t csts;
	uint8_t  en, rdy;
	int err;

	cc = nvme_mmio_read_4(ctrlr, cc);
	csts = nvme_mmio_read_4(ctrlr, csts);

	en = (cc >> NVME_CC_REG_EN_SHIFT) & NVME_CC_REG_EN_MASK;
	rdy = (csts >> NVME_CSTS_REG_RDY_SHIFT) & NVME_CSTS_REG_RDY_MASK;

	/*
	 * Per 3.1.5 in NVME 1.3 spec, transitioning CC.EN from 0 to 1
	 * when CSTS.RDY is 1 or transitioning CC.EN from 1 to 0 when
	 * CSTS.RDY is 0 "has undefined results" So make sure that CSTS.RDY
	 * isn't the desired value. Short circuit if we're already disabled.
	 */
	if (en == 1) {
		if (rdy == 0) {
			/* EN == 1, wait for  RDY == 1 or fail */
			err = nvme_ctrlr_wait_for_ready(ctrlr, 1);
			if (err != 0)
				return (err);
		}
	} else {
		/* EN == 0 already wait for RDY == 0 */
		if (rdy == 0)
			return (0);
		else
			return (nvme_ctrlr_wait_for_ready(ctrlr, 0));
	}

	cc &= ~NVME_CC_REG_EN_MASK;
	nvme_mmio_write_4(ctrlr, cc, cc);
	/*
	 * Some drives have issues with accessing the mmio after we
	 * disable, so delay for a bit after we write the bit to
	 * cope with these issues.
	 */
	if (ctrlr->quirks & QUIRK_DELAY_B4_CHK_RDY)
		pause("nvmeR", B4_CHK_RDY_DELAY_MS * hz / 1000);
	return (nvme_ctrlr_wait_for_ready(ctrlr, 0));
}