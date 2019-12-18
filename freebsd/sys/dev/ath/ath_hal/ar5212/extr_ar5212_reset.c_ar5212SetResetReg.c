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
typedef  int uint32_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  reg16 ;
struct TYPE_4__ {int ah_phyPowerOn; } ;
struct TYPE_3__ {scalar_t__ ah_bustype; scalar_t__ ah_ispcie; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH5212 (struct ath_hal*) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_CFG ; 
 int AR_CFG_SWRD ; 
 int AR_CFG_SWTD ; 
 int /*<<< orphan*/  AR_IER ; 
 int AR_IER_DISABLE ; 
 int /*<<< orphan*/  AR_ISR_RAC ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_BB ; 
 int AR_RC_MAC ; 
 int AR_RC_PCI ; 
 int /*<<< orphan*/  AR_RXDP ; 
 scalar_t__ HAL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int INIT_CONFIG_STATUS ; 
 int /*<<< orphan*/  IS_5112_REV5_UP (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_COMMON_CONFIG_STATUS ; 
 scalar_t__ ar5212MacStop (struct ath_hal*) ; 
 scalar_t__ ar5212SetPowerMode (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath_hal_read_pci_config_space (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ath_hal_wait (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ isBigEndian () ; 

__attribute__((used)) static HAL_BOOL
ar5212SetResetReg(struct ath_hal *ah, uint32_t resetMask)
{
	uint32_t mask = resetMask ? resetMask : ~0;
	HAL_BOOL rt;

	/* Never reset the PCIE core */
	if (AH_PRIVATE(ah)->ah_ispcie) {
		resetMask &= ~AR_RC_PCI;
	}

	if (resetMask & (AR_RC_MAC | AR_RC_PCI)) {
		/*
		 * To ensure that the driver can reset the
		 * MAC, wake up the chip
		 */
		rt = ar5212SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE);

		if (rt != AH_TRUE) {
			return rt;
		}

		/*
		 * Disable interrupts
		 */
		OS_REG_WRITE(ah, AR_IER, AR_IER_DISABLE);
		OS_REG_READ(ah, AR_IER);

		if (ar5212MacStop(ah) != AH_TRUE) {
			/*
			 * Failed to stop the MAC gracefully; let's be more forceful then
			 */

			/* need some delay before flush any pending MMR writes */
			OS_DELAY(15);
			OS_REG_READ(ah, AR_RXDP);

			resetMask |= AR_RC_MAC | AR_RC_BB;
			/* _Never_ reset PCI Express core */
			if (! AH_PRIVATE(ah)->ah_ispcie) {
				resetMask |= AR_RC_PCI;
			}
#if 0
			/*
			 * Flush the park address of the PCI controller
			*/
			/* Read PCI slot information less than Hainan revision */
			if (AH_PRIVATE(ah)->ah_bustype == HAL_BUS_TYPE_PCI) {
				if (!IS_5112_REV5_UP(ah)) {
#define PCI_COMMON_CONFIG_STATUS    0x06
					u_int32_t    i;
					u_int16_t    reg16;

					for (i = 0; i < 32; i++) {
						ath_hal_read_pci_config_space(ah,
						    PCI_COMMON_CONFIG_STATUS,
						    &reg16, sizeof(reg16));
					}
				}
#undef PCI_COMMON_CONFIG_STATUS
			}
#endif
		} else {
			/*
			 * MAC stopped gracefully; no need to warm-reset the PCI bus
			 */

			resetMask &= ~AR_RC_PCI;

			/* need some delay before flush any pending MMR writes */
			OS_DELAY(15);
			OS_REG_READ(ah, AR_RXDP);
		}
	}

	(void) OS_REG_READ(ah, AR_RXDP);/* flush any pending MMR writes */
	OS_REG_WRITE(ah, AR_RC, resetMask);
	OS_DELAY(15);			/* need to wait at least 128 clocks
					   when reseting PCI before read */
	mask &= (AR_RC_MAC | AR_RC_BB);
	resetMask &= (AR_RC_MAC | AR_RC_BB);
	rt = ath_hal_wait(ah, AR_RC, mask, resetMask);
        if ((resetMask & AR_RC_MAC) == 0) {
		if (isBigEndian()) {
			/*
			 * Set CFG, little-endian for descriptor accesses.
			 */
			mask = INIT_CONFIG_STATUS | AR_CFG_SWRD;
#ifndef AH_NEED_DESC_SWAP
			mask |= AR_CFG_SWTD;
#endif
			OS_REG_WRITE(ah, AR_CFG, mask);
		} else
			OS_REG_WRITE(ah, AR_CFG, INIT_CONFIG_STATUS);
		if (ar5212SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE))
			(void) OS_REG_READ(ah, AR_ISR_RAC);
	}

	/* track PHY power state so we don't try to r/w BB registers */
	AH5212(ah)->ah_phyPowerOn = ((resetMask & AR_RC_BB) == 0);
	return rt;
}