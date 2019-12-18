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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DIAG ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int jiffies_64 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mt_cycles ; 
 int /*<<< orphan*/  mt_scaling_div ; 
 int /*<<< orphan*/  mt_scaling_jiffies ; 
 int /*<<< orphan*/  mt_scaling_mult ; 
 int smp_cpu_mtid ; 
 int /*<<< orphan*/  stcctm (int /*<<< orphan*/ ,int,int*) ; 
 int* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_mt_scaling(void)
{
	u64 cycles_new[8], *cycles_old;
	u64 delta, fac, mult, div;
	int i;

	stcctm(MT_DIAG, smp_cpu_mtid + 1, cycles_new);
	cycles_old = this_cpu_ptr(mt_cycles);
	fac = 1;
	mult = div = 0;
	for (i = 0; i <= smp_cpu_mtid; i++) {
		delta = cycles_new[i] - cycles_old[i];
		div += delta;
		mult *= i + 1;
		mult += delta * fac;
		fac *= i + 1;
	}
	div *= fac;
	if (div > 0) {
		/* Update scaling factor */
		__this_cpu_write(mt_scaling_mult, mult);
		__this_cpu_write(mt_scaling_div, div);
		memcpy(cycles_old, cycles_new,
		       sizeof(u64) * (smp_cpu_mtid + 1));
	}
	__this_cpu_write(mt_scaling_jiffies, jiffies_64);
}