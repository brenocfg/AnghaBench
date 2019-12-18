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
struct _ccu_nm {unsigned long min_n; unsigned long max_n; unsigned long min_m; unsigned long max_m; unsigned long n; unsigned long m; } ;

/* Variables and functions */
 unsigned long ccu_nm_calc_rate (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void ccu_nm_find_best(unsigned long parent, unsigned long rate,
			     struct _ccu_nm *nm)
{
	unsigned long best_rate = 0;
	unsigned long best_n = 0, best_m = 0;
	unsigned long _n, _m;

	for (_n = nm->min_n; _n <= nm->max_n; _n++) {
		for (_m = nm->min_m; _m <= nm->max_m; _m++) {
			unsigned long tmp_rate = ccu_nm_calc_rate(parent,
								  _n, _m);

			if (tmp_rate > rate)
				continue;

			if ((rate - tmp_rate) < (rate - best_rate)) {
				best_rate = tmp_rate;
				best_n = _n;
				best_m = _m;
			}
		}
	}

	nm->n = best_n;
	nm->m = best_m;
}