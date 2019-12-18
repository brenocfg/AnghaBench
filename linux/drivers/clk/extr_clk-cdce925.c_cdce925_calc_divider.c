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
typedef  int u16 ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 

__attribute__((used)) static u16 cdce925_calc_divider(unsigned long rate,
		unsigned long parent_rate)
{
	unsigned long divider;

	if (!rate)
		return 0;
	if (rate >= parent_rate)
		return 1;

	divider = DIV_ROUND_CLOSEST(parent_rate, rate);
	if (divider > 0x7F)
		divider = 0x7F;

	return (u16)divider;
}