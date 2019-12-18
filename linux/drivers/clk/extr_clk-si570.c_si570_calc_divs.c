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
typedef  int uint8_t ;
typedef  int u64 ;
struct clk_si570 {int /*<<< orphan*/  fxtal; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
 int FDCO_MAX ; 
 int FDCO_MIN ; 
 int ULLONG_MAX ; 
 int div64_u64 (int,int /*<<< orphan*/ ) ; 
 int div_u64 (int,unsigned long) ; 

__attribute__((used)) static int si570_calc_divs(unsigned long frequency, struct clk_si570 *data,
		u64 *out_rfreq, unsigned int *out_n1, unsigned int *out_hs_div)
{
	int i;
	unsigned int n1, hs_div;
	u64 fdco, best_fdco = ULLONG_MAX;
	static const uint8_t si570_hs_div_values[] = { 11, 9, 7, 6, 5, 4 };

	for (i = 0; i < ARRAY_SIZE(si570_hs_div_values); i++) {
		hs_div = si570_hs_div_values[i];
		/* Calculate lowest possible value for n1 */
		n1 = div_u64(div_u64(FDCO_MIN, hs_div), frequency);
		if (!n1 || (n1 & 1))
			n1++;
		while (n1 <= 128) {
			fdco = (u64)frequency * (u64)hs_div * (u64)n1;
			if (fdco > FDCO_MAX)
				break;
			if (fdco >= FDCO_MIN && fdco < best_fdco) {
				*out_n1 = n1;
				*out_hs_div = hs_div;
				*out_rfreq = div64_u64(fdco << 28, data->fxtal);
				best_fdco = fdco;
			}
			n1 += (n1 == 1 ? 1 : 2);
		}
	}

	if (best_fdco == ULLONG_MAX)
		return -EINVAL;

	return 0;
}