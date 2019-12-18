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
struct TYPE_2__ {int /*<<< orphan*/  alt_stfle_fac_list; int /*<<< orphan*/  stfle_fac_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_KERNEL_NOBP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __clear_facility (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void setup_facility_list(void)
{
	memcpy(S390_lowcore.alt_stfle_fac_list,
	       S390_lowcore.stfle_fac_list,
	       sizeof(S390_lowcore.alt_stfle_fac_list));
	if (!IS_ENABLED(CONFIG_KERNEL_NOBP))
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
}