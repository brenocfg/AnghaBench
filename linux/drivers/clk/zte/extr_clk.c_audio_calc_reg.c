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
struct zx_clk_audio_div_table {unsigned long rate; unsigned int int_reg; unsigned int frac_reg; } ;
struct clk_zx_audio_divider {int dummy; } ;

/* Variables and functions */
 unsigned int CLK_AUDIO_DIV_INT_FRAC_MAX ; 
 unsigned int CLK_AUDIO_DIV_INT_FRAC_MIN ; 
 unsigned long gcd (unsigned long,unsigned long) ; 

__attribute__((used)) static void audio_calc_reg(struct clk_zx_audio_divider *audio_div,
			   struct zx_clk_audio_div_table *div_table,
			   unsigned long rate, unsigned long parent_rate)
{
	unsigned int reg_int, reg_frac;
	unsigned long m, n, div;

	reg_int = parent_rate / rate;

	if (reg_int > CLK_AUDIO_DIV_INT_FRAC_MAX)
		reg_int = CLK_AUDIO_DIV_INT_FRAC_MAX;
	else if (reg_int < CLK_AUDIO_DIV_INT_FRAC_MIN)
		reg_int = 0;
	m = parent_rate - rate * reg_int;
	n = rate;

	div = gcd(m, n);
	m = m / div;
	n = n / div;

	if ((m >> 16) || (n >> 16)) {
		if (m > n) {
			n = n * 0xffff / m;
			m = 0xffff;
		} else {
			m = m * 0xffff / n;
			n = 0xffff;
		}
	}
	reg_frac = m | (n << 16);

	div_table->rate = parent_rate * n / (reg_int * n + m);
	div_table->int_reg = reg_int;
	div_table->frac_reg = reg_frac;
}