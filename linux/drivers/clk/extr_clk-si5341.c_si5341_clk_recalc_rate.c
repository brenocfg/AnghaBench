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
typedef  unsigned int u32 ;
struct clk_si5341 {int freq_vco; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI5341_PLL_M_NUM ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int si5341_decode_44_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 struct clk_si5341* to_clk_si5341 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long si5341_clk_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_si5341 *data = to_clk_si5341(hw);
	int err;
	u64 res;
	u64 m_num;
	u32 m_den;
	unsigned int shift;

	/* Assume that PDIV is not being used, just read the PLL setting */
	err = si5341_decode_44_32(data->regmap, SI5341_PLL_M_NUM,
				&m_num, &m_den);
	if (err < 0)
		return 0;

	if (!m_num || !m_den)
		return 0;

	/*
	 * Though m_num is 64-bit, only the upper bits are actually used. While
	 * calculating m_num and m_den, they are shifted as far as possible to
	 * the left. To avoid 96-bit division here, we just shift them back so
	 * we can do with just 64 bits.
	 */
	shift = 0;
	res = m_num;
	while (res & 0xffff00000000ULL) {
		++shift;
		res >>= 1;
	}
	res *= parent_rate;
	do_div(res, (m_den >> shift));

	/* We cannot return the actual frequency in 32 bit, store it locally */
	data->freq_vco = res;

	/* Report kHz since the value is out of range */
	do_div(res, 1000);

	return (unsigned long)res;
}