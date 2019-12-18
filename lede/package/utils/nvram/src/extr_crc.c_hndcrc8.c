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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int* crc8_table ; 

uint8_t hndcrc8 (
	uint8_t * pdata,  /* pointer to array of data to process */
	uint32_t nbytes,  /* number of input data bytes to process */
	uint8_t crc       /* either CRC8_INIT_VALUE or previous return value */
) {
	while (nbytes-- > 0)
		crc = crc8_table[(crc ^ *pdata++) & 0xff];

	return crc;
}