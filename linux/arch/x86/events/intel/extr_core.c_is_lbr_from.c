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
struct TYPE_2__ {unsigned long lbr_from; unsigned long lbr_nr; } ;

/* Variables and functions */
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static bool is_lbr_from(unsigned long msr)
{
	unsigned long lbr_from_nr = x86_pmu.lbr_from + x86_pmu.lbr_nr;

	return x86_pmu.lbr_from <= msr && msr < lbr_from_nr;
}