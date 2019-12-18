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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int off_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int AR5315_MEM1_BASE ; 
 int /*<<< orphan*/  ATH_READ_REG (int) ; 

__attribute__((used)) static int
ar5315_spi_get_block(off_t offset, caddr_t data, off_t count)
{
	int i;
	for(i = 0; i < count / 4; ++i) {
		*((uint32_t *)data + i) = ATH_READ_REG(AR5315_MEM1_BASE + offset + i * 4);
	}
//	printf("ar5315_spi_get_blockr: %x %x %x\n", 
//		(int)offset, (int)count, *(uint32_t *)data);
	return (0);
}