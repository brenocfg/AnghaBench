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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HALASSERT (int) ; 
 int MAX_ANALOG_START ; 
 int ath_hal_reverseBits (int,int) ; 

void
ar5212ModifyRfBuffer(uint32_t *rfBuf, uint32_t reg32, uint32_t numBits,
                     uint32_t firstBit, uint32_t column)
{
#define	MAX_ANALOG_START	319		/* XXX */
	uint32_t tmp32, mask, arrayEntry, lastBit;
	int32_t bitPosition, bitsLeft;

	HALASSERT(column <= 3);
	HALASSERT(numBits <= 32);
	HALASSERT(firstBit + numBits <= MAX_ANALOG_START);

	tmp32 = ath_hal_reverseBits(reg32, numBits);
	arrayEntry = (firstBit - 1) / 8;
	bitPosition = (firstBit - 1) % 8;
	bitsLeft = numBits;
	while (bitsLeft > 0) {
		lastBit = (bitPosition + bitsLeft > 8) ?
			8 : bitPosition + bitsLeft;
		mask = (((1 << lastBit) - 1) ^ ((1 << bitPosition) - 1)) <<
			(column * 8);
		rfBuf[arrayEntry] &= ~mask;
		rfBuf[arrayEntry] |= ((tmp32 << bitPosition) <<
			(column * 8)) & mask;
		bitsLeft -= 8 - bitPosition;
		tmp32 = tmp32 >> (8 - bitPosition);
		bitPosition = 0;
		arrayEntry++;
	}
#undef MAX_ANALOG_START
}