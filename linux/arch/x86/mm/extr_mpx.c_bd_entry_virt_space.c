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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {unsigned long long x86_virt_bits; } ;

/* Variables and functions */
 unsigned long long MPX_BD_NR_ENTRIES_32 ; 
 unsigned long long MPX_BD_NR_ENTRIES_64 ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  is_64bit_mm (struct mm_struct*) ; 

__attribute__((used)) static inline unsigned long bd_entry_virt_space(struct mm_struct *mm)
{
	unsigned long long virt_space;
	unsigned long long GB = (1ULL << 30);

	/*
	 * This covers 32-bit emulation as well as 32-bit kernels
	 * running on 64-bit hardware.
	 */
	if (!is_64bit_mm(mm))
		return (4ULL * GB) / MPX_BD_NR_ENTRIES_32;

	/*
	 * 'x86_virt_bits' returns what the hardware is capable
	 * of, and returns the full >32-bit address space when
	 * running 32-bit kernels on 64-bit hardware.
	 */
	virt_space = (1ULL << boot_cpu_data.x86_virt_bits);
	return virt_space / MPX_BD_NR_ENTRIES_64;
}