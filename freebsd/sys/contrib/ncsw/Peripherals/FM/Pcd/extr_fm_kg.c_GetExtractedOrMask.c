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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t GetExtractedOrMask(uint8_t bitOffset, bool fqid)
{
    uint8_t i, mask, numOfOnesToClear, walking1Mask = 1;

    /* bitOffset 1-7 --> mask 0x1-0x7F */
    if (bitOffset<8)
    {
        mask = 0;
        for (i = 0 ; i < bitOffset ; i++, walking1Mask <<= 1)
            mask |= walking1Mask;
    }
    else
    {
       mask = 0xFF;
       numOfOnesToClear = 0;
       if (fqid && bitOffset>24)
           /* bitOffset 25-31 --> mask 0xFE-0x80 */
           numOfOnesToClear = (uint8_t)(bitOffset-24);
       else
          /* bitOffset 9-15 --> mask 0xFE-0x80 */
          if (!fqid && bitOffset>8)
               numOfOnesToClear = (uint8_t)(bitOffset-8);
       for (i = 0 ; i < numOfOnesToClear ; i++, walking1Mask <<= 1)
           mask &= ~walking1Mask;
       /* bitOffset 8-24 for FQID, 8 for PP --> no mask (0xFF)*/
    }
    return mask;
}