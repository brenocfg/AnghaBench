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
 int /*<<< orphan*/  AR_PHY (int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int ath_hal_reverseBits (int,int) ; 

uint32_t
ar5416GetRadioRev(struct ath_hal *ah)
{
	uint32_t val;
	int i;

	/* Read Radio Chip Rev Extract */
	OS_REG_WRITE(ah, AR_PHY(0x36), 0x00007058);
	for (i = 0; i < 8; i++)
		OS_REG_WRITE(ah, AR_PHY(0x20), 0x00010000);
	val = (OS_REG_READ(ah, AR_PHY(256)) >> 24) & 0xff;
	val = ((val & 0xf0) >> 4) | ((val & 0x0f) << 4);
	return ath_hal_reverseBits(val, 8);
}