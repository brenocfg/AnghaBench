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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CFG ; 
 int AR_CFG_SWRD ; 
 int AR_CFG_SWTD ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_RDMA ; 
 int AR_RC_RMAC ; 
 int AR_RC_RPCU ; 
 int AR_RC_RPHY ; 
 int INIT_CONFIG_STATUS ; 
 int /*<<< orphan*/  OS_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_wait (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ isBigEndian () ; 

__attribute__((used)) static HAL_BOOL
ar5210SetResetReg(struct ath_hal *ah, uint32_t resetMask, u_int delay)
{
	uint32_t mask = resetMask ? resetMask : ~0;
	HAL_BOOL rt;

	OS_REG_WRITE(ah, AR_RC, resetMask);
	/* need to wait at least 128 clocks when reseting PCI before read */
	OS_DELAY(delay);

	resetMask &= AR_RC_RPCU | AR_RC_RDMA | AR_RC_RPHY | AR_RC_RMAC;
	mask &= AR_RC_RPCU | AR_RC_RDMA | AR_RC_RPHY | AR_RC_RMAC;
	rt = ath_hal_wait(ah, AR_RC, mask, resetMask);
        if ((resetMask & AR_RC_RMAC) == 0) {
		if (isBigEndian()) {
			/*
			 * Set CFG, little-endian for descriptor accesses.
			 */
			mask = INIT_CONFIG_STATUS | AR_CFG_SWTD | AR_CFG_SWRD;
			OS_REG_WRITE(ah, AR_CFG, mask);
		} else
			OS_REG_WRITE(ah, AR_CFG, INIT_CONFIG_STATUS);
	}
	return rt;
}