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
struct _ccu_nkm {unsigned long min_k; unsigned long max_k; unsigned long min_n; unsigned long max_n; unsigned long min_m; unsigned long max_m; unsigned long n; unsigned long k; unsigned long m; } ;

/* Variables and functions */

__attribute__((used)) static void ccu_nkm_find_best(unsigned long parent, unsigned long rate,
			      struct _ccu_nkm *nkm)
{
	unsigned long best_rate = 0;
	unsigned long best_n = 0, best_k = 0, best_m = 0;
	unsigned long _n, _k, _m;

	for (_k = nkm->min_k; _k <= nkm->max_k; _k++) {
		for (_n = nkm->min_n; _n <= nkm->max_n; _n++) {
			for (_m = nkm->min_m; _m <= nkm->max_m; _m++) {
				unsigned long tmp_rate;

				tmp_rate = parent * _n * _k / _m;

				if (tmp_rate > rate)
					continue;
				if ((rate - tmp_rate) < (rate - best_rate)) {
					best_rate = tmp_rate;
					best_n = _n;
					best_k = _k;
					best_m = _m;
				}
			}
		}
	}

	nkm->n = best_n;
	nkm->k = best_k;
	nkm->m = best_m;
}