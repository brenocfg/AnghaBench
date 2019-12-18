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
struct alt_region {struct alt_instr* end; struct alt_instr* begin; } ;
struct alt_instr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_NPATCHABLE ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __alt_instructions ; 
 scalar_t__ __alt_instructions_end ; 
 int /*<<< orphan*/  __apply_alternatives (struct alt_region*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_alternatives_applied ; 
 int /*<<< orphan*/  bitmap_complement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_capabilities ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  remaining_capabilities ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static int __apply_alternatives_multi_stop(void *unused)
{
	struct alt_region region = {
		.begin	= (struct alt_instr *)__alt_instructions,
		.end	= (struct alt_instr *)__alt_instructions_end,
	};

	/* We always have a CPU 0 at this point (__init) */
	if (smp_processor_id()) {
		while (!READ_ONCE(all_alternatives_applied))
			cpu_relax();
		isb();
	} else {
		DECLARE_BITMAP(remaining_capabilities, ARM64_NPATCHABLE);

		bitmap_complement(remaining_capabilities, boot_capabilities,
				  ARM64_NPATCHABLE);

		BUG_ON(all_alternatives_applied);
		__apply_alternatives(&region, false, remaining_capabilities);
		/* Barriers provided by the cache flushing */
		WRITE_ONCE(all_alternatives_applied, 1);
	}

	return 0;
}