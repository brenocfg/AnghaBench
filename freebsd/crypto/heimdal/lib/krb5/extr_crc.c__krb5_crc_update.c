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

/* Variables and functions */
 int* table ; 

uint32_t
_krb5_crc_update (const char *p, size_t len, uint32_t res)
{
    while (len--)
	res = table[(res ^ *p++) & 0xFF] ^ (res >> 8);
    return res & 0xFFFFFFFF;
}