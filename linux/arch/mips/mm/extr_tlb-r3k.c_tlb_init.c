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

/* Variables and functions */
#define  CPU_TX3922 129 
#define  CPU_TX3927 128 
 int /*<<< orphan*/  build_tlb_refill_handler () ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  local_flush_tlb_from (int /*<<< orphan*/ ) ; 
 int r3k_have_wired_reg ; 
 int /*<<< orphan*/  write_c0_wired (int /*<<< orphan*/ ) ; 

void tlb_init(void)
{
	switch (current_cpu_type()) {
	case CPU_TX3922:
	case CPU_TX3927:
		r3k_have_wired_reg = 1;
		write_c0_wired(0);		/* Set to 8 on reset... */
		break;
	}
	local_flush_tlb_from(0);
	build_tlb_refill_handler();
}