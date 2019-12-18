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
typedef  int u_short ;
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */
 int* crc16_table ; 

__attribute__((used)) static u_short
wlpsacrc(u_char *buf, u_int len)
{
    u_short     crc = 0;
    int         i, r1;
    
    for (i = 0; i < len; i++, buf++) {
        /* lower 4 bits */
        r1 = crc16_table[crc & 0xF];
        crc = (crc >> 4) & 0x0FFF;
        crc = crc ^ r1 ^ crc16_table[*buf & 0xF];
        
        /* upper 4 bits */
        r1 = crc16_table[crc & 0xF];
        crc = (crc >> 4) & 0x0FFF;
        crc = crc ^ r1 ^ crc16_table[(*buf >> 4) & 0xF];
    }
    return(crc);
}