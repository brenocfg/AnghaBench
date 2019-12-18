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
typedef  int u8 ;
struct factors_request {int rate; int k; int p; int n; scalar_t__ m; } ;

/* Variables and functions */

__attribute__((used)) static void sun8i_a23_get_pll1_factors(struct factors_request *req)
{
	u8 div;

	/* Normalize value to a 6M multiple */
	div = req->rate / 6000000;
	req->rate = 6000000 * div;

	/* m is always zero for pll1 */
	req->m = 0;

	/* k is 1 only on these cases */
	if (req->rate >= 768000000 || req->rate == 42000000 ||
			req->rate == 54000000)
		req->k = 1;
	else
		req->k = 0;

	/* p will be 2 for divs under 20 and odd divs under 32 */
	if (div < 20 || (div < 32 && (div & 1)))
		req->p = 2;

	/* p will be 1 for even divs under 32, divs under 40 and odd pairs
	 * of divs between 40-62 */
	else if (div < 40 || (div < 64 && (div & 2)))
		req->p = 1;

	/* any other entries have p = 0 */
	else
		req->p = 0;

	/* calculate a suitable n based on k and p */
	div <<= req->p;
	div /= (req->k + 1);
	req->n = div / 4 - 1;
}