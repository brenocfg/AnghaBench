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
typedef  int uint32_t ;
struct aw_clk_nmm_sc {int /*<<< orphan*/  m1; int /*<<< orphan*/  m0; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int aw_clk_factor_get_max (int /*<<< orphan*/ *) ; 
 int aw_clk_factor_get_min (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
aw_clk_nmm_find_best(struct aw_clk_nmm_sc *sc, uint64_t fparent, uint64_t *fout,
  uint32_t *factor_n, uint32_t *factor_m0, uint32_t *factor_m1)
{
	uint64_t cur, best;
	uint32_t n, m0, m1;
	uint32_t max_n, max_m0, max_m1;
	uint32_t min_n, min_m0, min_m1;

	*factor_n = *factor_m0 = *factor_m1 = 0;

	max_n = aw_clk_factor_get_max(&sc->n);
	min_n = aw_clk_factor_get_min(&sc->n);
	max_m0 = aw_clk_factor_get_max(&sc->m0);
	min_m0 = aw_clk_factor_get_min(&sc->m0);
	max_m1 = aw_clk_factor_get_max(&sc->m1);
	min_m1 = aw_clk_factor_get_min(&sc->m1);

	for (m0 = min_m0; m0 <= max_m0; ) {
		for (m1 = min_m1; m1 <= max_m1; ) {
			for (n = min_n; n <= max_n; ) {
				cur = fparent * n / m0 / m1;
				if (abs(*fout - cur) < abs(*fout - best)) {
					best = cur;
					*factor_n = n;
					*factor_m0 = m0;
					*factor_m1 = m1;
				}
				n++;
			}
			m1++;
		}
		m0++;
	}

	return (best);
}