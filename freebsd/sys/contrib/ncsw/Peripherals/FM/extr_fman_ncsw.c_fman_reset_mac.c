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
struct fman_fpm_regs {int /*<<< orphan*/  fm_rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int FPM_RSTC_10G0_RESET ; 
 int FPM_RSTC_10G1_RESET ; 
 int FPM_RSTC_1G0_RESET ; 
 int FPM_RSTC_1G1_RESET ; 
 int FPM_RSTC_1G2_RESET ; 
 int FPM_RSTC_1G3_RESET ; 
 int FPM_RSTC_1G4_RESET ; 
 int FPM_RSTC_1G5_RESET ; 
 int FPM_RSTC_1G6_RESET ; 
 int FPM_RSTC_1G7_RESET ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_reset_mac(struct fman_fpm_regs *fpm_rg, uint8_t mac_id, bool is_10g)
{
	uint32_t msk, timeout = 100;

	/* Get the relevant bit mask */
	if (is_10g) {
		switch (mac_id) {
		case(0):
			msk = FPM_RSTC_10G0_RESET;
			break;
        case(1):
            msk = FPM_RSTC_10G1_RESET;
            break;
		default:
			return -EINVAL;
		}
	} else {
		switch (mac_id) {
		case(0):
			msk = FPM_RSTC_1G0_RESET;
			break;
		case(1):
			msk = FPM_RSTC_1G1_RESET;
			break;
		case(2):
			msk = FPM_RSTC_1G2_RESET;
			break;
		case(3):
			msk = FPM_RSTC_1G3_RESET;
			break;
		case(4):
			msk = FPM_RSTC_1G4_RESET;
			break;
        case (5):
            msk = FPM_RSTC_1G5_RESET;
            break;
        case (6):
            msk = FPM_RSTC_1G6_RESET;
            break;
        case (7):
            msk = FPM_RSTC_1G7_RESET;
            break;
		default:
			return -EINVAL;
		}
	}
	/* reset */
	iowrite32be(msk, &fpm_rg->fm_rstc);
	while ((ioread32be(&fpm_rg->fm_rstc) & msk) && --timeout)
		DELAY(10);

	if (!timeout)
		return -EBUSY;
	return 0;
}