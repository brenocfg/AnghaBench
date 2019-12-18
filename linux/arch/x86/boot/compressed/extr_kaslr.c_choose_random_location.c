#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  loadflags; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASLR_FLAG ; 
 int /*<<< orphan*/  LOAD_PHYSICAL_ADDR ; 
 int X86_CR4_LA57 ; 
 int __pgtable_l5_enabled ; 
 int __read_cr4 () ; 
 int /*<<< orphan*/  add_identity_map (unsigned long,unsigned long) ; 
 TYPE_2__* boot_params ; 
 scalar_t__ cmdline_find_option_bool (char*) ; 
 int /*<<< orphan*/  finalize_identity_maps () ; 
 unsigned long find_random_phys_addr (unsigned long,unsigned long) ; 
 unsigned long find_random_virt_addr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  initialize_identity_maps () ; 
 int /*<<< orphan*/  mem_avoid_init (unsigned long,unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int pgdir_shift ; 
 int ptrs_per_p4d ; 
 int /*<<< orphan*/  warn (char*) ; 

void choose_random_location(unsigned long input,
			    unsigned long input_size,
			    unsigned long *output,
			    unsigned long output_size,
			    unsigned long *virt_addr)
{
	unsigned long random_addr, min_addr;

	if (cmdline_find_option_bool("nokaslr")) {
		warn("KASLR disabled: 'nokaslr' on cmdline.");
		return;
	}

#ifdef CONFIG_X86_5LEVEL
	if (__read_cr4() & X86_CR4_LA57) {
		__pgtable_l5_enabled = 1;
		pgdir_shift = 48;
		ptrs_per_p4d = 512;
	}
#endif

	boot_params->hdr.loadflags |= KASLR_FLAG;

	/* Prepare to add new identity pagetables on demand. */
	initialize_identity_maps();

	/* Record the various known unsafe memory ranges. */
	mem_avoid_init(input, input_size, *output);

	/*
	 * Low end of the randomization range should be the
	 * smaller of 512M or the initial kernel image
	 * location:
	 */
	min_addr = min(*output, 512UL << 20);

	/* Walk available memory entries to find a random address. */
	random_addr = find_random_phys_addr(min_addr, output_size);
	if (!random_addr) {
		warn("Physical KASLR disabled: no suitable memory region!");
	} else {
		/* Update the new physical address location. */
		if (*output != random_addr) {
			add_identity_map(random_addr, output_size);
			*output = random_addr;
		}

		/*
		 * This loads the identity mapping page table.
		 * This should only be done if a new physical address
		 * is found for the kernel, otherwise we should keep
		 * the old page table to make it be like the "nokaslr"
		 * case.
		 */
		finalize_identity_maps();
	}


	/* Pick random virtual address starting from LOAD_PHYSICAL_ADDR. */
	if (IS_ENABLED(CONFIG_X86_64))
		random_addr = find_random_virt_addr(LOAD_PHYSICAL_ADDR, output_size);
	*virt_addr = random_addr;
}