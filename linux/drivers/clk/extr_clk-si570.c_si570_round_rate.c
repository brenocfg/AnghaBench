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
typedef  unsigned long u64 ;
struct clk_si570 {unsigned long frequency; unsigned long rfreq; unsigned int n1; unsigned int hs_div; TYPE_1__* i2c_client; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long long abs (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long div64_u64 (unsigned long,int) ; 
 int si570_calc_divs (unsigned long,struct clk_si570*,unsigned long*,unsigned int*,unsigned int*) ; 
 struct clk_si570* to_clk_si570 (struct clk_hw*) ; 

__attribute__((used)) static long si570_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	int err;
	u64 rfreq;
	unsigned int n1, hs_div;
	struct clk_si570 *data = to_clk_si570(hw);

	if (!rate)
		return 0;

	if (div64_u64(abs(rate - data->frequency) * 10000LL,
				data->frequency) < 35) {
		rfreq = div64_u64((data->rfreq * rate) +
				div64_u64(data->frequency, 2), data->frequency);
		n1 = data->n1;
		hs_div = data->hs_div;

	} else {
		err = si570_calc_divs(rate, data, &rfreq, &n1, &hs_div);
		if (err) {
			dev_err(&data->i2c_client->dev,
					"unable to round rate\n");
			return 0;
		}
	}

	return rate;
}