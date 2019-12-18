#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cpuinfo_x86 {int dummy; } ;
struct TYPE_2__ {scalar_t__ succor; scalar_t__ smca; } ;

/* Variables and functions */
 int MASK_CNTP_HI ; 
 int MASK_LOCKED_HI ; 
 int MASK_VALID_HI ; 
 unsigned int NR_BLOCKS ; 
 int /*<<< orphan*/  deferred_error_interrupt_enable (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  disable_err_thresholding (struct cpuinfo_x86*,unsigned int) ; 
 int get_block_address (int,int,int,unsigned int,unsigned int,unsigned int) ; 
 TYPE_1__ mce_flags ; 
 int /*<<< orphan*/  mce_num_banks ; 
 int prepare_threshold_block (unsigned int,unsigned int,int,int,int) ; 
 scalar_t__ rdmsr_safe (int,int*,int*) ; 
 int /*<<< orphan*/  smca_configure (unsigned int,unsigned int) ; 
 unsigned int smp_processor_id () ; 
 unsigned int this_cpu_read (int /*<<< orphan*/ ) ; 

void mce_amd_feature_init(struct cpuinfo_x86 *c)
{
	unsigned int bank, block, cpu = smp_processor_id();
	u32 low = 0, high = 0, address = 0;
	int offset = -1;


	for (bank = 0; bank < this_cpu_read(mce_num_banks); ++bank) {
		if (mce_flags.smca)
			smca_configure(bank, cpu);

		disable_err_thresholding(c, bank);

		for (block = 0; block < NR_BLOCKS; ++block) {
			address = get_block_address(address, low, high, bank, block, cpu);
			if (!address)
				break;

			if (rdmsr_safe(address, &low, &high))
				break;

			if (!(high & MASK_VALID_HI))
				continue;

			if (!(high & MASK_CNTP_HI)  ||
			     (high & MASK_LOCKED_HI))
				continue;

			offset = prepare_threshold_block(bank, block, address, offset, high);
		}
	}

	if (mce_flags.succor)
		deferred_error_interrupt_enable(c);
}