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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

uint16_t
create_osi_cksum (const uint8_t *pptr, int checksum_offset, int length)
{

    int x;
    int y;
    uint32_t mul;
    uint32_t c0;
    uint32_t c1;
    uint16_t checksum;
    int idx;

    c0 = 0;
    c1 = 0;

    for (idx = 0; idx < length; idx++) {
        /*
         * Ignore the contents of the checksum field.
         */
        if (idx == checksum_offset ||
            idx == checksum_offset+1) {
            c1 += c0;
            pptr++;
        } else {
            c0 = c0 + *(pptr++);
            c1 += c0;
        }
    }

    c0 = c0 % 255;
    c1 = c1 % 255;

    mul = (length - checksum_offset)*(c0);

    x = mul - c0 - c1;
    y = c1 - mul - 1;

    if ( y >= 0 ) y++;
    if ( x < 0 ) x--;

    x %= 255;
    y %= 255;


    if (x == 0) x = 255;
    if (y == 0) y = 255;

    y &= 0x00FF;
    checksum = ((x << 8) | y);

    return checksum;
}