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
 int /*<<< orphan*/  disabled_wait () ; 
 int /*<<< orphan*/  print_machine_type () ; 
 int /*<<< orphan*/  print_missing_facilities () ; 
 int /*<<< orphan*/  sclp_early_printk (char*) ; 

__attribute__((used)) static void facility_mismatch(void)
{
	sclp_early_printk("The Linux kernel requires more recent processor hardware\n");
	print_machine_type();
	print_missing_facilities();
	sclp_early_printk("See Principles of Operations for facility bits\n");
	disabled_wait();
}