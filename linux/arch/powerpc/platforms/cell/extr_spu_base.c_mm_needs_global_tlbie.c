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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int NR_CPUS ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 

__attribute__((used)) static inline void mm_needs_global_tlbie(struct mm_struct *mm)
{
	int nr = (NR_CPUS > 1) ? NR_CPUS : NR_CPUS + 1;

	/* Global TLBIE broadcast required with SPEs. */
	bitmap_fill(cpumask_bits(mm_cpumask(mm)), nr);
}