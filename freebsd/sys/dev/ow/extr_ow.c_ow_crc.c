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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t* ow_crc_table ; 

__attribute__((used)) static uint8_t
ow_crc(device_t ndev, device_t pdev, uint8_t *buffer, size_t len)
{
	uint8_t crc = 0;
	int i;

	for (i = 0; i < len; i++)
		crc = ow_crc_table[crc ^ buffer[i]];
	return crc;
}