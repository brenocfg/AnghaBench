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
typedef  int uint16_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {struct ieee80211_channel* ah_curchan; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY (int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int ath_hal_gethwchannel (struct ath_hal*,struct ieee80211_channel*) ; 
 int ath_hal_reverseBits (int,int) ; 

__attribute__((used)) static HAL_BOOL
ar5210SetChannel(struct ath_hal *ah, struct ieee80211_channel *chan)
{
	uint16_t freq = ath_hal_gethwchannel(ah, chan);
	uint32_t data;

	/* Set the Channel */
	data = ath_hal_reverseBits((freq - 5120)/10, 5);
	data = (data << 1) | 0x41;
	OS_REG_WRITE(ah, AR_PHY(0x27), data);
	OS_REG_WRITE(ah, AR_PHY(0x30), 0);
	AH_PRIVATE(ah)->ah_curchan = chan;
	return AH_TRUE;
}