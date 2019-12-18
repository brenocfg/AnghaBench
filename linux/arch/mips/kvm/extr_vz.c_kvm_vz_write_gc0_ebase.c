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
 long MIPS_EBASE_WG ; 
 scalar_t__ cpu_has_ebase_wg ; 
 scalar_t__ cpu_has_mips64r6 ; 
 int /*<<< orphan*/  write_gc0_ebase (long) ; 
 int /*<<< orphan*/  write_gc0_ebase_64 (long) ; 

__attribute__((used)) static inline void kvm_vz_write_gc0_ebase(long v)
{
	/*
	 * First write with WG=1 to write upper bits, then write again in case
	 * WG should be left at 0.
	 * write_gc0_ebase_64() is no longer UNDEFINED since R6.
	 */
	if (sizeof(long) == 8 &&
	    (cpu_has_mips64r6 || cpu_has_ebase_wg)) {
		write_gc0_ebase_64(v | MIPS_EBASE_WG);
		write_gc0_ebase_64(v);
	} else {
		write_gc0_ebase(v | MIPS_EBASE_WG);
		write_gc0_ebase(v);
	}
}