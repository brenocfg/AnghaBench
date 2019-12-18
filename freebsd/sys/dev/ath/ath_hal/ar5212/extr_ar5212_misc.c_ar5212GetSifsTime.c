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
typedef  int u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_D_GBL_IFS_SIFS ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int ath_hal_mac_usec (struct ath_hal*,int) ; 

u_int
ar5212GetSifsTime(struct ath_hal *ah)
{
	u_int clks = OS_REG_READ(ah, AR_D_GBL_IFS_SIFS) & 0xffff;
	return ath_hal_mac_usec(ah, clks)+2;	/* convert from system clocks */
}