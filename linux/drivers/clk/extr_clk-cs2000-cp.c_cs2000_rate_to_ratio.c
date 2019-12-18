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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 cs2000_rate_to_ratio(u32 rate_in, u32 rate_out)
{
	u64 ratio;

	/*
	 * ratio = rate_out / rate_in * 2^20
	 *
	 * To avoid over flow, rate_out is u64.
	 * The result should be u32.
	 */
	ratio = (u64)rate_out << 20;
	do_div(ratio, rate_in);

	return ratio;
}