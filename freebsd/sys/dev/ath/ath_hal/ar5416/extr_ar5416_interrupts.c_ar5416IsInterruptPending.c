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
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_INTR_ASYNC_CAUSE ; 
 int AR_INTR_MAC_IRQ ; 
 int AR_INTR_SPURIOUS ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int AR_INTR_SYNC_DEFAULT ; 
 scalar_t__ AR_SREV_HOWL (struct ath_hal*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5416IsInterruptPending(struct ath_hal *ah)
{
	uint32_t isr;

	if (AR_SREV_HOWL(ah))
		return AH_TRUE;

	/* 
	 * Some platforms trigger our ISR before applying power to
	 * the card, so make sure the INTPEND is really 1, not 0xffffffff.
	 */
	isr = OS_REG_READ(ah, AR_INTR_ASYNC_CAUSE);
	if (isr != AR_INTR_SPURIOUS && (isr & AR_INTR_MAC_IRQ) != 0)
		return AH_TRUE;

	isr = OS_REG_READ(ah, AR_INTR_SYNC_CAUSE);
	if (isr != AR_INTR_SPURIOUS && (isr & AR_INTR_SYNC_DEFAULT))
		return AH_TRUE;

	return AH_FALSE;
}