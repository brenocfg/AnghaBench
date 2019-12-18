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
struct aw_clk_nkmp_sc {int flags; int update_shift; int lock_retries; int lock_shift; int /*<<< orphan*/  offset; TYPE_1__ p; TYPE_1__ m; TYPE_1__ k; TYPE_1__ n; } ;

/* Variables and functions */
 int AW_CLK_HAS_LOCK ; 
 int AW_CLK_HAS_UPDATE ; 
 int AW_CLK_SCALE_CHANGE ; 
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
 scalar_t__ aw_clk_nkmp_find_best (struct aw_clk_nkmp_sc*,scalar_t__,scalar_t__*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  aw_clk_nkmp_set_freq_scale (struct clknode*,struct aw_clk_nkmp_sc*,int,int,int,int) ; 
 struct aw_clk_nkmp_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
aw_clk_nkmp_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct aw_clk_nkmp_sc *sc;
	uint64_t best;
	uint32_t val, best_n, best_k, best_m, best_p;
	int retry;

	sc = clknode_get_softc(clk);

	best = aw_clk_nkmp_find_best(sc, fparent, fout,
	    &best_n, &best_k, &best_m, &best_p);
	if ((flags & CLK_SET_DRYRUN) != 0) {
		*fout = best;
		*stop = 1;
		return (0);
	}

	if ((best < *fout) &&
	  ((flags & CLK_SET_ROUND_DOWN) != 0)) {
		*stop = 1;
		return (ERANGE);
	}
	if ((best > *fout) &&
	  ((flags & CLK_SET_ROUND_UP) != 0)) {
		*stop = 1;
		return (ERANGE);
	}

	if ((sc->flags & AW_CLK_SCALE_CHANGE) != 0)
		aw_clk_nkmp_set_freq_scale(clk, sc,
		    best_n, best_k, best_m, best_p);
	else {
		DEVICE_LOCK(clk);
		READ4(clk, sc->offset, &val);
		val &= ~sc->n.mask;
		val &= ~sc->k.mask;
		val &= ~sc->m.mask;
		val &= ~sc->p.mask;
		val |= aw_clk_factor_get_value(&sc->n, best_n) << sc->n.shift;
		val |= aw_clk_factor_get_value(&sc->k, best_k) << sc->k.shift;
		val |= aw_clk_factor_get_value(&sc->m, best_m) << sc->m.shift;
		val |= aw_clk_factor_get_value(&sc->p, best_p) << sc->p.shift;
		WRITE4(clk, sc->offset, val);
		DELAY(2000);
		DEVICE_UNLOCK(clk);

		if ((sc->flags & AW_CLK_HAS_UPDATE) != 0) {
			DEVICE_LOCK(clk);
			READ4(clk, sc->offset, &val);
			val |= 1 << sc->update_shift;
			WRITE4(clk, sc->offset, val);
			DELAY(2000);
			DEVICE_UNLOCK(clk);
		}

		if ((sc->flags & AW_CLK_HAS_LOCK) != 0) {
			for (retry = 0; retry < sc->lock_retries; retry++) {
				READ4(clk, sc->offset, &val);
				if ((val & (1 << sc->lock_shift)) != 0)
					break;
				DELAY(1000);
			}
		}
	}

	*fout = best;
	*stop = 1;

	return (0);
}