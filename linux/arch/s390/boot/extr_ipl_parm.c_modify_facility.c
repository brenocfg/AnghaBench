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
struct TYPE_2__ {int /*<<< orphan*/  stfle_fac_list; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __clear_facility (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_facility (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void modify_facility(unsigned long nr, bool clear)
{
	if (clear)
		__clear_facility(nr, S390_lowcore.stfle_fac_list);
	else
		__set_facility(nr, S390_lowcore.stfle_fac_list);
}