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

/* Variables and functions */
 int /*<<< orphan*/  AH_MARK_RX_CTL ; 
 int /*<<< orphan*/  AH_MARK_RX_CTL_PCU_STOP ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212DisableMibCounters (struct ath_hal*) ; 

void
ar5212StopPcuReceive(struct ath_hal *ah)
{
	OS_MARK(ah, AH_MARK_RX_CTL, AH_MARK_RX_CTL_PCU_STOP);
	OS_REG_WRITE(ah, AR_DIAG_SW,
		OS_REG_READ(ah, AR_DIAG_SW) | AR_DIAG_RX_DIS);
	ar5212DisableMibCounters(ah);
}