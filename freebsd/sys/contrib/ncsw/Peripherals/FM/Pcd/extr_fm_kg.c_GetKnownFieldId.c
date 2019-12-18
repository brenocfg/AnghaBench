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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t GetKnownFieldId(uint32_t bitMask)
{
    uint8_t cnt = 0;

    while (bitMask)
        if (bitMask & 0x80000000)
            break;
        else
        {
            cnt++;
            bitMask <<= 1;
        }
    return cnt;

}