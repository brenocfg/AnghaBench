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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_M_FRAC_DEN ; 
 unsigned long DELTA_M_FRAC_NUM ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long si544_max_delta(unsigned long rate)
{
	u64 num = rate;

	num *= DELTA_M_FRAC_NUM;
	do_div(num, DELTA_M_FRAC_DEN);

	return num;
}