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
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int AR_PCU_MISC_MODE2 ; 
 int AR_PCU_MISC_MODE2_ADHOC_MCAST_KEYID_ENABLE ; 
 int AR_PCU_MISC_MODE2_HWWAR1 ; 
 int AR_PCU_MISC_MODE2_HWWAR2 ; 
 int /*<<< orphan*/  AR_SREV_5416_V20_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_9271 (struct ath_hal*) ; 
 scalar_t__ AR_SREV_HOWL (struct ath_hal*) ; 
 scalar_t__ AR_SREV_KIWI_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_MERLIN (struct ath_hal*) ; 
 scalar_t__ AR_SREV_MERLIN_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SOWL (struct ath_hal*) ; 
 int OS_REG_READ (struct ath_hal*,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 
 int /*<<< orphan*/  ar5416SetRifsDelay (struct ath_hal*,struct ieee80211_channel const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5416OverrideIni(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	uint32_t val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear if off only after
	 * RXE is set for MAC. This prevents frames with corrupted
	 * descriptor status.
	 */
	OS_REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	if (AR_SREV_MERLIN_10_OR_LATER(ah)) {
		val = OS_REG_READ(ah, AR_PCU_MISC_MODE2);
		val &= (~AR_PCU_MISC_MODE2_ADHOC_MCAST_KEYID_ENABLE);
		if (!AR_SREV_9271(ah))
			val &= ~AR_PCU_MISC_MODE2_HWWAR1;

		if (AR_SREV_KIWI_10_OR_LATER(ah))
			val = val & (~AR_PCU_MISC_MODE2_HWWAR2);

		OS_REG_WRITE(ah, AR_PCU_MISC_MODE2, val);
	}

	/*
	 * Disable RIFS search on some chips to avoid baseband
	 * hang issues.
	 */
	if (AR_SREV_HOWL(ah) || AR_SREV_SOWL(ah))
		(void) ar5416SetRifsDelay(ah, chan, AH_FALSE);

        if (!AR_SREV_5416_V20_OR_LATER(ah) || AR_SREV_MERLIN(ah))
		return;

	/*
	 * Disable BB clock gating
	 * Necessary to avoid issues on AR5416 2.0
	 */
	OS_REG_WRITE(ah, 0x9800 + (651 << 2), 0x11);
}