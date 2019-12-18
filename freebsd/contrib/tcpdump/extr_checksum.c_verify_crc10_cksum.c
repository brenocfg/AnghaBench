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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int* crc10_table ; 

uint16_t
verify_crc10_cksum(uint16_t accum, const u_char *p, int length)
{
    register int i;

    for ( i = 0;  i < length;  i++ )
    {
        accum = ((accum << 8) & 0x3ff)
            ^ crc10_table[( accum >> 2) & 0xff]
            ^ *p++;
    }
    return accum;
}