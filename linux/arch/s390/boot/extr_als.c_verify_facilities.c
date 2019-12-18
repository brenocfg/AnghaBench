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
struct TYPE_2__ {int* stfle_fac_list; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __stfle (int*,int) ; 
 int* als ; 
 int /*<<< orphan*/  facility_mismatch () ; 

void verify_facilities(void)
{
	int i;

	__stfle(S390_lowcore.stfle_fac_list, ARRAY_SIZE(S390_lowcore.stfle_fac_list));
	for (i = 0; i < ARRAY_SIZE(als); i++) {
		if ((S390_lowcore.stfle_fac_list[i] & als[i]) != als[i])
			facility_mismatch();
	}
}