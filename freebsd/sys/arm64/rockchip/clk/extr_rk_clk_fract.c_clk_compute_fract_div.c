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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static void
clk_compute_fract_div(
	uint64_t n_input, uint64_t d_input,
	uint64_t n_max, uint64_t d_max,
	uint64_t *n_out, uint64_t *d_out)
{
	uint64_t n_prev, d_prev;	/* previous convergents */
	uint64_t n_cur, d_cur;		/* current  convergents */
	uint64_t n_rem, d_rem;		/* fraction remainder */
	uint64_t tmp, fact;

	/* Initialize fraction reminder */
	n_rem = n_input;
	d_rem = d_input;

	/* Init convergents to 0/1 and 1/0 */
	n_prev = 0;
	d_prev = 1;
	n_cur = 1;
	d_cur = 0;

	while (d_rem != 0 && n_cur < n_max && d_cur < d_max) {
		/* Factor for this step. */
		fact = n_rem / d_rem;

		/* Adjust fraction reminder */
		tmp = d_rem;
		d_rem = n_rem % d_rem;
		n_rem = tmp;

		/* Compute new nominator and save last one */
		tmp = n_prev + fact * n_cur;
		n_prev = n_cur;
		n_cur = tmp;

		/* Compute new denominator and save last one */
		tmp = d_prev + fact * d_cur;
		d_prev = d_cur;
		d_cur = tmp;
	}

	if (n_cur > n_max || d_cur > d_max) {
		*n_out = n_prev;
		*d_out = d_prev;
	} else {
		*n_out = n_cur;
		*d_out = d_cur;
	}
}