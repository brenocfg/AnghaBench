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
 int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 

__attribute__((used)) static inline int zynqmp_divider_get_val(unsigned long parent_rate,
					 unsigned long rate)
{
	return DIV_ROUND_CLOSEST(parent_rate, rate);
}