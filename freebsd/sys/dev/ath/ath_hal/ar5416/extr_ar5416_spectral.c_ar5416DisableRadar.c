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
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int AR_PHY_RADAR_0_ENA ; 
 int AR_PHY_RADAR_0_FFT_ENA ; 
 int AR_PHY_RADAR_0_HEIGHT ; 
 int AR_PHY_RADAR_0_RRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_EXT ; 
 int AR_PHY_RADAR_EXT_ENA ; 
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int /*<<< orphan*/  MAX_RADAR_HEIGHT ; 
 int /*<<< orphan*/  MAX_RADAR_RSSI_THRESH ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5416DisableRadar(struct ath_hal *ah)
{
	uint32_t val;

	// Enable radar FFT
	val = OS_REG_READ(ah, AR_PHY_RADAR_0);
	val |= AR_PHY_RADAR_0_FFT_ENA;

	// set radar detect thresholds to max to effectively disable radar
	val &= ~AR_PHY_RADAR_0_RRSSI;
	val |= SM(MAX_RADAR_RSSI_THRESH, AR_PHY_RADAR_0_RRSSI);

	val &= ~AR_PHY_RADAR_0_HEIGHT;
	val |= SM(MAX_RADAR_HEIGHT, AR_PHY_RADAR_0_HEIGHT);

	val &= ~(AR_PHY_RADAR_0_ENA);
	OS_REG_WRITE(ah, AR_PHY_RADAR_0, val);

	// disable extension radar detect
	val = OS_REG_READ(ah, AR_PHY_RADAR_EXT);
	OS_REG_WRITE(ah, AR_PHY_RADAR_EXT, val & ~AR_PHY_RADAR_EXT_ENA);

	val = OS_REG_READ(ah, AR_RX_FILTER);
	val |= (1<<13);
	OS_REG_WRITE(ah, AR_RX_FILTER, val);
}