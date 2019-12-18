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
struct n2rng {int hvapi_major; } ;

/* Variables and functions */
 unsigned long N2RNG_ACCUM_CYCLES_DEFAULT ; 
 unsigned long sun4v_rng_data_read_diag_v1 (unsigned long,unsigned long,unsigned long*) ; 
 unsigned long sun4v_rng_data_read_diag_v2 (unsigned long,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static unsigned long n2rng_read_diag_data_one(struct n2rng *np,
					      unsigned long unit,
					      unsigned long data_ra,
					      unsigned long data_len,
					      unsigned long *ticks)
{
	unsigned long hv_err;

	if (np->hvapi_major == 1) {
		hv_err = sun4v_rng_data_read_diag_v1(data_ra, data_len, ticks);
	} else {
		hv_err = sun4v_rng_data_read_diag_v2(data_ra, data_len,
						     unit, ticks);
		if (!*ticks)
			*ticks = N2RNG_ACCUM_CYCLES_DEFAULT;
	}
	return hv_err;
}