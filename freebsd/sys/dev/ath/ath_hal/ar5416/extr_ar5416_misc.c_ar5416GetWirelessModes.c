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
typedef  int u_int ;
struct TYPE_2__ {scalar_t__ halHTSupport; } ;
struct ath_hal_private {TYPE_1__ ah_caps; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;

/* Variables and functions */
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11G ; 
 int HAL_MODE_11NA_HT20 ; 
 int HAL_MODE_11NA_HT40MINUS ; 
 int HAL_MODE_11NA_HT40PLUS ; 
 int HAL_MODE_11NG_HT20 ; 
 int HAL_MODE_11NG_HT40MINUS ; 
 int HAL_MODE_11NG_HT40PLUS ; 
 int ar5212GetWirelessModes (struct ath_hal*) ; 

u_int
ar5416GetWirelessModes(struct ath_hal *ah)
{
	u_int mode;
	struct ath_hal_private *ahpriv = AH_PRIVATE(ah);
	HAL_CAPABILITIES *pCap = &ahpriv->ah_caps;

	mode = ar5212GetWirelessModes(ah);

	/* Only enable HT modes if the NIC supports HT */
	if (pCap->halHTSupport == AH_TRUE && (mode & HAL_MODE_11A))
		mode |= HAL_MODE_11NA_HT20
		     |  HAL_MODE_11NA_HT40PLUS
		     |  HAL_MODE_11NA_HT40MINUS
		     ;
	if (pCap->halHTSupport == AH_TRUE && (mode & HAL_MODE_11G))
		mode |= HAL_MODE_11NG_HT20
		     |  HAL_MODE_11NG_HT40PLUS
		     |  HAL_MODE_11NG_HT40MINUS
		     ;
	return mode;
}