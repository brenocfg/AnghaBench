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
typedef  scalar_t__ u32 ;
struct factors_request {int rate; int parent_rate; int k; int m; int n; } ;

/* Variables and functions */
 scalar_t__ round_down (scalar_t__,int) ; 

__attribute__((used)) static void sun6i_a31_get_pll1_factors(struct factors_request *req)
{
	/*
	 * We can operate only on MHz, this will make our life easier
	 * later.
	 */
	u32 freq_mhz = req->rate / 1000000;
	u32 parent_freq_mhz = req->parent_rate / 1000000;

	/*
	 * Round down the frequency to the closest multiple of either
	 * 6 or 16
	 */
	u32 round_freq_6 = round_down(freq_mhz, 6);
	u32 round_freq_16 = round_down(freq_mhz, 16);

	if (round_freq_6 > round_freq_16)
		freq_mhz = round_freq_6;
	else
		freq_mhz = round_freq_16;

	req->rate = freq_mhz * 1000000;

	/* If the frequency is a multiple of 32 MHz, k is always 3 */
	if (!(freq_mhz % 32))
		req->k = 3;
	/* If the frequency is a multiple of 9 MHz, k is always 2 */
	else if (!(freq_mhz % 9))
		req->k = 2;
	/* If the frequency is a multiple of 8 MHz, k is always 1 */
	else if (!(freq_mhz % 8))
		req->k = 1;
	/* Otherwise, we don't use the k factor */
	else
		req->k = 0;

	/*
	 * If the frequency is a multiple of 2 but not a multiple of
	 * 3, m is 3. This is the first time we use 6 here, yet we
	 * will use it on several other places.
	 * We use this number because it's the lowest frequency we can
	 * generate (with n = 0, k = 0, m = 3), so every other frequency
	 * somehow relates to this frequency.
	 */
	if ((freq_mhz % 6) == 2 || (freq_mhz % 6) == 4)
		req->m = 2;
	/*
	 * If the frequency is a multiple of 6MHz, but the factor is
	 * odd, m will be 3
	 */
	else if ((freq_mhz / 6) & 1)
		req->m = 3;
	/* Otherwise, we end up with m = 1 */
	else
		req->m = 1;

	/* Calculate n thanks to the above factors we already got */
	req->n = freq_mhz * (req->m + 1) / ((req->k + 1) * parent_freq_mhz)
		 - 1;

	/*
	 * If n end up being outbound, and that we can still decrease
	 * m, do it.
	 */
	if ((req->n + 1) > 31 && (req->m + 1) > 1) {
		req->n = (req->n + 1) / 2 - 1;
		req->m = (req->m + 1) / 2 - 1;
	}
}