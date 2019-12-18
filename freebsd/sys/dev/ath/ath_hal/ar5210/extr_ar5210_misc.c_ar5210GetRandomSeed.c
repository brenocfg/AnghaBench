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
 scalar_t__ AR_PHY_BASE ; 
 scalar_t__ AR_TSF_L32 ; 
 scalar_t__ AR_TSF_U32 ; 
 int OS_REG_READ (struct ath_hal*,scalar_t__) ; 

uint32_t
ar5210GetRandomSeed(struct ath_hal *ah)
{
	uint32_t nf;

	nf = (OS_REG_READ(ah, AR_PHY_BASE + (25 << 2)) >> 19) & 0x1ff;
	if (nf & 0x100)
		nf = 0 - ((nf ^ 0x1ff) + 1);
	return (OS_REG_READ(ah, AR_TSF_U32) ^
		OS_REG_READ(ah, AR_TSF_L32) ^ nf);
}