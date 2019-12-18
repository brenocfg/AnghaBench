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
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long MIPS_CDMMBASE_ADDR_SHIFT ; 
 unsigned long MIPS_CDMMBASE_ADDR_START ; 
 unsigned long MIPS_CDMMBASE_EN ; 
 unsigned long read_c0_cdmmbase () ; 

__attribute__((used)) static phys_addr_t mips_cdmm_cur_base(void)
{
	unsigned long cdmmbase = read_c0_cdmmbase();

	if (!(cdmmbase & MIPS_CDMMBASE_EN))
		return 0;

	return (cdmmbase >> MIPS_CDMMBASE_ADDR_SHIFT)
		<< MIPS_CDMMBASE_ADDR_START;
}