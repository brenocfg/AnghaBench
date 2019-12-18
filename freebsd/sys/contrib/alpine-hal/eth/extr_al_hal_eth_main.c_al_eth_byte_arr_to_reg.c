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

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_assert (int) ; 

__attribute__((used)) static inline void al_eth_byte_arr_to_reg(
		uint32_t *reg, uint8_t *arr, unsigned int num_bytes)
{
	uint32_t mask = 0xff;
	unsigned int i;

	al_assert(num_bytes <= 4);

	*reg = 0;

	for (i = 0 ; i < num_bytes ; i++) {
		AL_REG_FIELD_SET(*reg, mask, (sizeof(uint8_t) * i), arr[i]);
		mask = mask << sizeof(uint8_t);
	}
}