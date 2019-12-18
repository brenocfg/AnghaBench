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
 int endian32 ; 

__attribute__((used)) static uint32_t
read32(uint32_t val)
{
	uint32_t temp;
	uint32_t endian;

	endian = endian32;
	temp = 0;

	while (val) {
		temp |= (val & 0xF) << ((endian & 0xF) * 4);
		endian >>= 4;
		val >>= 4;
	}
	return (temp);
}