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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct clknode {int dummy; } ;
struct TYPE_2__ {int mask; int shift; } ;
struct aw_clk_nmm_sc {int flags; int lock_retries; int lock_shift; int /*<<< orphan*/  offset; TYPE_1__ m1; TYPE_1__ m0; TYPE_1__ n; } ;

/* Variables and functions */
 int AW_CLK_HAS_LOCK ; 
 int CLK_SET_DRYRUN ; 
 int CLK_SET_ROUND_DOWN ; 
 int CLK_SET_ROUND_UP ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int ERANGE ; 
 int /*<<< orphan*/  READ4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,int /*<<< orphan*/ ,int) ; 
 int aw_clk_factor_get_value (TYPE_1__*,int) ; 
 scalar_t__ aw_clk_nmm_find_best (struct aw_clk_nmm_sc*,scalar_t__,scalar_t__*,int*,int*,int*) ; 
 struct aw_clk_nmm_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
aw_clk_nmm_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct aw_clk_nmm_sc *sc;
	uint64_t cur, best;
	uint32_t val, n, m0, m1, best_n, best_m0, best_m1;
	int retry;

	sc = clknode_get_softc(clk);

	best = cur = 0;

	best = aw_clk_nmm_find_best(sc, fparent, fout,
	    &best_n, &best_m0, &best_m1);

	if ((flags & CLK_SET_DRYRUN) != 0) {
		*fout = best;
		*stop = 1;
		return (0);
	}

	if ((best < *fout) &&
	  ((flags & CLK_SET_ROUND_DOWN) == 0)) {
		*stop = 1;
		return (ERANGE);
	}
	if ((best > *fout) &&
	  ((flags & CLK_SET_ROUND_UP) == 0)) {
		*stop = 1;
		return (ERANGE);
	}

	DEVICE_LOCK(clk);
	READ4(clk, sc->offset, &val);

	n = aw_clk_factor_get_value(&sc->n, best_n);
	m0 = aw_clk_factor_get_value(&sc->m0, best_m0);
	m1 = aw_clk_factor_get_value(&sc->m1, best_m1);
	val &= ~sc->n.mask;
	val &= ~sc->m0.mask;
	val &= ~sc->m1.mask;
	val |= n << sc->n.shift;
	val |= m0 << sc->m0.shift;
	val |= m1 << sc->m1.shift;

	WRITE4(clk, sc->offset, val);
	DEVICE_UNLOCK(clk);

	if ((sc->flags & AW_CLK_HAS_LOCK) != 0) {
		for (retry = 0; retry < sc->lock_retries; retry++) {
			READ4(clk, sc->offset, &val);
			if ((val & (1 << sc->lock_shift)) != 0)
				break;
			DELAY(1000);
		}
	}

	*fout = best;
	*stop = 1;

	return (0);
}