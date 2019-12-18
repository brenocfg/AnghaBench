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
 int* Crc16Table ; 

__attribute__((used)) static uint16_t
Crc16(uint16_t crc, u_char *cp, int len)
{
	while (len--)
		crc = (crc >> 8) ^ Crc16Table[(crc ^ *cp++) & 0xff];
	return (crc);
}