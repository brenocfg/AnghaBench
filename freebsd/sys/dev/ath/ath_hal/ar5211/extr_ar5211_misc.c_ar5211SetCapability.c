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
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_diagreg; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
#define  HAL_CAP_DIAG 128 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_setcapability (struct ath_hal*,int,int,int,int /*<<< orphan*/ *) ; 

HAL_BOOL
ar5211SetCapability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
	uint32_t capability, uint32_t setting, HAL_STATUS *status)
{
	switch (type) {
	case HAL_CAP_DIAG:		/* hardware diagnostic support */
		/*
		 * NB: could split this up into virtual capabilities,
		 *     (e.g. 1 => ACK, 2 => CTS, etc.) but it hardly
		 *     seems worth the additional complexity.
		 */
#ifdef AH_DEBUG
		AH_PRIVATE(ah)->ah_diagreg = setting;
#else
		AH_PRIVATE(ah)->ah_diagreg = setting & 0x6;	/* ACK+CTS */
#endif
		OS_REG_WRITE(ah, AR_DIAG_SW, AH_PRIVATE(ah)->ah_diagreg);
		return AH_TRUE;
	default:
		return ath_hal_setcapability(ah, type, capability,
			setting, status);
	}
}