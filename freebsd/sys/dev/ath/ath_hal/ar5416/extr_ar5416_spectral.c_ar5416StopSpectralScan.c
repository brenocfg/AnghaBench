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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_ERR_MASK_REG ; 
 int AR_PHY_ERR_RADAR ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int AR_PHY_SPECTRAL_SCAN_ACTIVE ; 
 int AR_PHY_SPECTRAL_SCAN_ENA ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5416StopSpectralScan(struct ath_hal *ah)
{
	uint32_t val;
	val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

	// Deactivate spectral scan
	val &= ~AR_PHY_SPECTRAL_SCAN_ENA;
	val &= ~AR_PHY_SPECTRAL_SCAN_ACTIVE;
	OS_REG_WRITE(ah, AR_PHY_SPECTRAL_SCAN, val);
	val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);
	val = OS_REG_READ(ah, AR_PHY_ERR_MASK_REG) & (~AR_PHY_ERR_RADAR);
	OS_REG_WRITE(ah, AR_PHY_ERR_MASK_REG, val);
}