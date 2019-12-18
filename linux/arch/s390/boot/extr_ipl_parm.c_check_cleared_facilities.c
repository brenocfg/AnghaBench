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
struct TYPE_2__ {unsigned long* stfle_fac_list; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 unsigned long FACILITIES_ALS ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  print_missing_facilities () ; 
 int /*<<< orphan*/  sclp_early_printk (char*) ; 

__attribute__((used)) static void check_cleared_facilities(void)
{
	unsigned long als[] = { FACILITIES_ALS };
	int i;

	for (i = 0; i < ARRAY_SIZE(als); i++) {
		if ((S390_lowcore.stfle_fac_list[i] & als[i]) != als[i]) {
			sclp_early_printk("Warning: The Linux kernel requires facilities cleared via command line option\n");
			print_missing_facilities();
			break;
		}
	}
}