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
 int EINVAL ; 
 int INT_MAX ; 
 int PCG_DIV_MAX ; 
 int PCG_PREDIV_MAX ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int imx8m_clk_composite_compute_dividers(unsigned long rate,
						unsigned long parent_rate,
						int *prediv, int *postdiv)
{
	int div1, div2;
	int error = INT_MAX;
	int ret = -EINVAL;

	*prediv = 1;
	*postdiv = 1;

	for (div1 = 1; div1 <= PCG_PREDIV_MAX; div1++) {
		for (div2 = 1; div2 <= PCG_DIV_MAX; div2++) {
			int new_error = ((parent_rate / div1) / div2) - rate;

			if (abs(new_error) < abs(error)) {
				*prediv = div1;
				*postdiv = div2;
				error = new_error;
				ret = 0;
			}
		}
	}
	return ret;
}