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
typedef  int u_int32_t ;
struct ath_hal_5416 {int ah_btCoexBTWeight; int ah_btCoexWLANWeight; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 
 void* AR5416_BT_WGHT ; 
 void* AR5416_STOMP_ALL_FORCE_WLAN_WGHT ; 
 void* AR5416_STOMP_ALL_WLAN_WGHT ; 
 void* AR5416_STOMP_LOW_FORCE_WLAN_WGHT ; 
 void* AR5416_STOMP_LOW_WLAN_WGHT ; 
 void* AR5416_STOMP_NONE_WLAN_WGHT ; 
 scalar_t__ AR_SREV_KIWI_10_OR_LATER (struct ath_hal*) ; 
#define  HAL_BT_COEX_NO_STOMP 134 
#define  HAL_BT_COEX_STOMP_ALL 133 
#define  HAL_BT_COEX_STOMP_ALL_FORCE 132 
#define  HAL_BT_COEX_STOMP_AUDIO 131 
#define  HAL_BT_COEX_STOMP_LOW 130 
#define  HAL_BT_COEX_STOMP_LOW_FORCE 129 
#define  HAL_BT_COEX_STOMP_NONE 128 

void
ar5416BTCoexSetWeights(struct ath_hal *ah, u_int32_t stompType)
{
	struct ath_hal_5416 *ahp = AH5416(ah);

	if (AR_SREV_KIWI_10_OR_LATER(ah)) {
		/* TODO: TX RX separate is not enabled. */
		switch (stompType) {
		case HAL_BT_COEX_STOMP_AUDIO:
			/* XXX TODO */
		case HAL_BT_COEX_STOMP_ALL:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_ALL_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_LOW:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_LOW_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_ALL_FORCE:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight =
			    AR5416_STOMP_ALL_FORCE_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_LOW_FORCE:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight =
			    AR5416_STOMP_LOW_FORCE_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_NONE:
		case HAL_BT_COEX_NO_STOMP:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_NONE_WLAN_WGHT;
			break;
		default:
			/* There is a forceWeight from registry */
			ahp->ah_btCoexBTWeight = stompType & 0xffff;
			ahp->ah_btCoexWLANWeight = stompType >> 16;
			break;
		}
	} else {
		switch (stompType) {
		case HAL_BT_COEX_STOMP_AUDIO:
			/* XXX TODO */
		case HAL_BT_COEX_STOMP_ALL:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_ALL_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_LOW:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_LOW_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_ALL_FORCE:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight =
			    AR5416_STOMP_ALL_FORCE_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_LOW_FORCE:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight =
			    AR5416_STOMP_LOW_FORCE_WLAN_WGHT;
			break;
		case HAL_BT_COEX_STOMP_NONE:
		case HAL_BT_COEX_NO_STOMP:
			ahp->ah_btCoexBTWeight = AR5416_BT_WGHT;
			ahp->ah_btCoexWLANWeight = AR5416_STOMP_NONE_WLAN_WGHT;
			break;
		default:
			/* There is a forceWeight from registry */
			ahp->ah_btCoexBTWeight = stompType & 0xffff;
			ahp->ah_btCoexWLANWeight = stompType >> 16;
			break;
		}
	}
}