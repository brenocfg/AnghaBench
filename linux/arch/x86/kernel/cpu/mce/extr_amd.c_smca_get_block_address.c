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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_MISC (unsigned int) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_MISCy (unsigned int,unsigned int) ; 
 int per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smca_misc_banks_map ; 

__attribute__((used)) static u32 smca_get_block_address(unsigned int bank, unsigned int block,
				  unsigned int cpu)
{
	if (!block)
		return MSR_AMD64_SMCA_MCx_MISC(bank);

	if (!(per_cpu(smca_misc_banks_map, cpu) & BIT(bank)))
		return 0;

	return MSR_AMD64_SMCA_MCx_MISCy(bank, block - 1);
}