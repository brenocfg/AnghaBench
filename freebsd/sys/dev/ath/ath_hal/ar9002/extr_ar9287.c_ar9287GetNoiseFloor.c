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
struct ath_hal {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR9280_PHY_CH1_EXT_MINCCA_PWR ; 
 int /*<<< orphan*/  AR9280_PHY_CH1_MINCCA_PWR ; 
 int /*<<< orphan*/  AR9280_PHY_EXT_MINCCA_PWR ; 
 int /*<<< orphan*/  AR9280_PHY_MINCCA_PWR ; 
 int /*<<< orphan*/  AR_PHY_CCA ; 
 int /*<<< orphan*/  AR_PHY_CH1_CCA ; 
 int /*<<< orphan*/  AR_PHY_CH1_EXT_CCA ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HAL_DEBUG_NFCAL ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar9287GetNoiseFloor(struct ath_hal *ah, int16_t nfarray[])
{
	int16_t nf;

	nf = MS(OS_REG_READ(ah, AR_PHY_CCA), AR9280_PHY_MINCCA_PWR);
	if (nf & 0x100)
		nf = 0 - ((nf ^ 0x1ff) + 1);
	HALDEBUG(ah, HAL_DEBUG_NFCAL,
	    "NF calibrated [ctl] [chain 0] is %d\n", nf);
	nfarray[0] = nf;

	nf = MS(OS_REG_READ(ah, AR_PHY_CH1_CCA), AR9280_PHY_CH1_MINCCA_PWR);
	if (nf & 0x100)
		nf = 0 - ((nf ^ 0x1ff) + 1);
	HALDEBUG(ah, HAL_DEBUG_NFCAL,
	    "NF calibrated [ctl] [chain 1] is %d\n", nf);
	nfarray[1] = nf;

	nf = MS(OS_REG_READ(ah, AR_PHY_EXT_CCA), AR9280_PHY_EXT_MINCCA_PWR);
	if (nf & 0x100)
		nf = 0 - ((nf ^ 0x1ff) + 1);
	HALDEBUG(ah, HAL_DEBUG_NFCAL,
	    "NF calibrated [ext] [chain 0] is %d\n", nf);
	nfarray[3] = nf;

	nf = MS(OS_REG_READ(ah, AR_PHY_CH1_EXT_CCA), AR9280_PHY_CH1_EXT_MINCCA_PWR);
	if (nf & 0x100)
		nf = 0 - ((nf ^ 0x1ff) + 1);
	HALDEBUG(ah, HAL_DEBUG_NFCAL,
	    "NF calibrated [ext] [chain 1] is %d\n", nf);
	nfarray[4] = nf;

        /* Chain 2 - invalid */
        nfarray[2] = 0;
        nfarray[5] = 0;

}