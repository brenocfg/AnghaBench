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
 scalar_t__ dmaf_continue (unsigned long) ; 
 scalar_t__ dmaf_p_disabled_continue (unsigned long) ; 

__attribute__((used)) static int src_cnt_flags(unsigned int src_cnt, unsigned long flags)
{
	if (dmaf_p_disabled_continue(flags))
		return src_cnt + 1;
	else if (dmaf_continue(flags))
		return src_cnt + 3;
	else
		return src_cnt;
}