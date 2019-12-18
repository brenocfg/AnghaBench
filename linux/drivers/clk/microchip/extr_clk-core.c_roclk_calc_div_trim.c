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
 int REFO_DIV_MASK ; 
 int REFO_TRIM_MAX ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 

__attribute__((used)) static void roclk_calc_div_trim(unsigned long rate,
				unsigned long parent_rate,
				u32 *rodiv_p, u32 *rotrim_p)
{
	u32 div, rotrim, rodiv;
	u64 frac;

	/* Find integer approximation of floating-point arithmetic.
	 *      fout = fin / [2 * {rodiv + (rotrim / 512)}] ... (1)
	 * i.e. fout = fin / 2 * DIV
	 *      whereas DIV = rodiv + (rotrim / 512)
	 *
	 * Since kernel does not perform floating-point arithmatic so
	 * (rotrim/512) will be zero. And DIV & rodiv will result same.
	 *
	 * ie. fout = (fin * 256) / [(512 * rodiv) + rotrim]  ... from (1)
	 * ie. rotrim = ((fin * 256) / fout) - (512 * DIV)
	 */
	if (parent_rate <= rate) {
		div = 0;
		frac = 0;
		rodiv = 0;
		rotrim = 0;
	} else {
		div = parent_rate / (rate << 1);
		frac = parent_rate;
		frac <<= 8;
		do_div(frac, rate);
		frac -= (u64)(div << 9);

		rodiv = (div > REFO_DIV_MASK) ? REFO_DIV_MASK : div;
		rotrim = (frac >= REFO_TRIM_MAX) ? REFO_TRIM_MAX : frac;
	}

	if (rodiv_p)
		*rodiv_p = rodiv;

	if (rotrim_p)
		*rotrim_p = rotrim;
}