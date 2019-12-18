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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t jboot_checksum(uint16_t start_val, uint16_t *data, int size)
{
	uint32_t counter = start_val;
	uint16_t *ptr = data;

	while (size > 1) {
		counter += *ptr;
		++ptr;
		while (counter >> 16)
			counter = (uint16_t) counter + (counter >> 16);
		size -= 2;
	}
	if (size > 0) {
		counter += *(uint8_t *) ptr;
		counter -= 0xFF;
	}
	while (counter >> 16)
		counter = (uint16_t) counter + (counter >> 16);
	return counter;
}