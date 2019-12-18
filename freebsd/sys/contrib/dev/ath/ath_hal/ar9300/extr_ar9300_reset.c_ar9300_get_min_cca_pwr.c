#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  int int16_t ;
struct TYPE_4__ {int nf_cw_int_delta; TYPE_1__* nfp; } ;
struct TYPE_3__ {int nominal; } ;

/* Variables and functions */
 TYPE_2__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR9280_PHY_MINCCA_PWR ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 int /*<<< orphan*/  AR_PHY_CCA_0 ; 
 int BAD_SCAN_NF_MARGIN ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

int16_t ar9300_get_min_cca_pwr(struct ath_hal *ah)
{
    int16_t nf;
//    struct ath_hal_private *ahpriv = AH_PRIVATE(ah);


    if ((OS_REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF) == 0) {
        nf = MS(OS_REG_READ(ah, AR_PHY_CCA_0), AR9280_PHY_MINCCA_PWR);
        if (nf & 0x100) {
            nf = 0 - ((nf ^ 0x1ff) + 1);
        }
    } else {
        /* NF calibration is not done, assume CW interference */
        nf = AH9300(ah)->nfp->nominal + AH9300(ah)->nf_cw_int_delta +
            BAD_SCAN_NF_MARGIN;
    }
    return nf;
}