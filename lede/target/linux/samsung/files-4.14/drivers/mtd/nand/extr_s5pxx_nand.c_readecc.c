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
typedef  unsigned int uint8_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int readl (void*) ; 

__attribute__((used)) static void readecc(void *eccbase, uint8_t *ecc_code, unsigned ecc_len)
{
	uint32_t i, j, reg;

	for (i = 0; i < ecc_len; i += 4) {
		reg = readl(eccbase + i);
		for (j = 0; (j < 4) && (i + j < ecc_len); ++j) {
			ecc_code[i + j] = reg & 0xFF;
			reg >>= 8;
		}
	}
}