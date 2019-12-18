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
typedef  int u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_DEFAULT_ANTENNA ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5210SetDefAntenna(struct ath_hal *ah, u_int antenna)
{
	uint32_t val = OS_REG_READ(ah, AR_STA_ID1);

	if (antenna != (val & AR_STA_ID1_DEFAULT_ANTENNA ?  2 : 1)) {
		/*
		 * Antenna change requested, force a toggle of the default.
		 */
		OS_REG_WRITE(ah, AR_STA_ID1, val | AR_STA_ID1_DEFAULT_ANTENNA);
	}
}