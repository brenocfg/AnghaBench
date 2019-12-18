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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 

__attribute__((used)) static u32 e1000_calc_rx_da_crc(u8 mac[])
{
	u32 poly = 0xEDB88320;	/* Polynomial for 802.3 CRC calculation */
	u32 i, j, mask, crc;

	DEBUGFUNC("e1000_calc_rx_da_crc");

	crc = 0xffffffff;
	for (i = 0; i < 6; i++) {
		crc = crc ^ mac[i];
		for (j = 8; j > 0; j--) {
			mask = (crc & 1) * (-1);
			crc = (crc >> 1) ^ (poly & mask);
		}
	}
	return ~crc;
}