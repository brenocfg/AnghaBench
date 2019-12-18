#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int flags; } ;
struct aw_clk_nkmp_sc {TYPE_1__ n; TYPE_1__ k; TYPE_1__ m; TYPE_1__ p; } ;

/* Variables and functions */
 int AW_CLK_FACTOR_POWER_OF_TWO ; 
 scalar_t__ aw_clk_factor_get_max (TYPE_1__*) ; 
 scalar_t__ aw_clk_factor_get_min (TYPE_1__*) ; 

__attribute__((used)) static uint64_t
aw_clk_nkmp_find_best(struct aw_clk_nkmp_sc *sc, uint64_t fparent, uint64_t *fout,
    uint32_t *factor_n, uint32_t *factor_k, uint32_t *factor_m, uint32_t *factor_p)
{
	uint64_t cur, best;
	uint32_t n, k, m, p;

	best = 0;
	*factor_n = 0;
	*factor_k = 0;
	*factor_m = 0;
	*factor_p = 0;

	for (n = aw_clk_factor_get_min(&sc->n); n <= aw_clk_factor_get_max(&sc->n); ) {
		for (k = aw_clk_factor_get_min(&sc->k); k <= aw_clk_factor_get_max(&sc->k); ) {
			for (m = aw_clk_factor_get_min(&sc->m); m <= aw_clk_factor_get_max(&sc->m); ) {
				for (p = aw_clk_factor_get_min(&sc->p); p <= aw_clk_factor_get_max(&sc->p); ) {
					cur = (fparent * n * k) / (m * p);
					if ((*fout - cur) < (*fout - best)) {
						best = cur;
						*factor_n = n;
						*factor_k = k;
						*factor_m = m;
						*factor_p = p;
					}
					if (best == *fout)
						return (best);
					if ((sc->p.flags & AW_CLK_FACTOR_POWER_OF_TWO) != 0)
						p <<= 1;
					else
						p++;
				}
				if ((sc->m.flags & AW_CLK_FACTOR_POWER_OF_TWO) != 0)
					m <<= 1;
				else
					m++;
			}
			if ((sc->k.flags & AW_CLK_FACTOR_POWER_OF_TWO) != 0)
				k <<= 1;
			else
				k++;
		}
		if ((sc->n.flags & AW_CLK_FACTOR_POWER_OF_TWO) != 0)
			n <<= 1;
		else
			n++;
	}

	return best;
}