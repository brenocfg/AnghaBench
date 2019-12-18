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
struct benchmarks {int member_1; char* member_2; int /*<<< orphan*/  title; int /*<<< orphan*/  offset; scalar_t__ fn; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  benchmark_nop ; 
 int /*<<< orphan*/  benchmark_pushpop1 ; 
 int /*<<< orphan*/  benchmark_pushpop2 ; 
 int /*<<< orphan*/  benchmark_pushpop3 ; 
 int /*<<< orphan*/  benchmark_pushpop4 ; 
 int /*<<< orphan*/  benchmark_pushpop_thumb ; 
 int kprobe_benchmark (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int run_benchmarks(void)
{
	int ret;
	struct benchmarks list[] = {
		{&benchmark_nop, 0, "nop"},
		/*
		 * benchmark_pushpop{1,3} will have the optimised
		 * instruction emulation, whilst benchmark_pushpop{2,4} will
		 * be the equivalent unoptimised instructions.
		 */
		{&benchmark_pushpop1, 0, "stmdb	sp!, {r3-r11,lr}"},
		{&benchmark_pushpop1, 4, "ldmia	sp!, {r3-r11,pc}"},
		{&benchmark_pushpop2, 0, "stmdb	sp!, {r0-r8,lr}"},
		{&benchmark_pushpop2, 4, "ldmia	sp!, {r0-r8,pc}"},
		{&benchmark_pushpop3, 0, "stmdb	sp!, {r4,lr}"},
		{&benchmark_pushpop3, 4, "ldmia	sp!, {r4,pc}"},
		{&benchmark_pushpop4, 0, "stmdb	sp!, {r0,lr}"},
		{&benchmark_pushpop4, 4, "ldmia	sp!, {r0,pc}"},
#ifdef CONFIG_THUMB2_KERNEL
		{&benchmark_pushpop_thumb, 0, "push.n	{r0-r7,lr}"},
		{&benchmark_pushpop_thumb, 2, "pop.n	{r0-r7,pc}"},
#endif
		{0}
	};

	struct benchmarks *b;
	for (b = list; b->fn; ++b) {
		ret = kprobe_benchmark(b->fn, b->offset);
		if (ret < 0)
			return ret;
		pr_info("    %dns for kprobe %s\n", ret, b->title);
	}

	pr_info("\n");
	return 0;
}