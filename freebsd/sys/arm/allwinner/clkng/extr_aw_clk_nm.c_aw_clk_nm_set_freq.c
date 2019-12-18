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
struct aw_clk_nm_sc {int flags; int lock_retries; int lock_shift; int /*<<< orphan*/  offset; TYPE_1__ m; TYPE_1__ n; } ;

/* Variables and functions */
 int AW_CLK_HAS_LOCK ; 
 int AW_CLK_REPARENT ; 
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
 scalar_t__ aw_clk_nm_find_best (struct aw_clk_nm_sc*,scalar_t__,scalar_t__*,int*,int*) ; 
 struct clknode* clknode_find_by_name (char const*) ; 
 int /*<<< orphan*/  clknode_get_freq (struct clknode*,scalar_t__*) ; 
 struct clknode* clknode_get_parent (struct clknode*) ; 
 int clknode_get_parent_idx (struct clknode*) ; 
 char** clknode_get_parent_names (struct clknode*) ; 
 int clknode_get_parents_num (struct clknode*) ; 
 struct aw_clk_nm_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_set_parent_by_idx (struct clknode*,int) ; 

__attribute__((used)) static int
aw_clk_nm_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct aw_clk_nm_sc *sc;
	struct clknode *p_clk;
	const char **p_names;
	uint64_t cur, best;
	uint32_t val, m, n, best_m, best_n;
	int p_idx, best_parent, retry;

	sc = clknode_get_softc(clk);

	best = cur = 0;
	best_parent = 0;

	if ((sc->flags & AW_CLK_REPARENT) != 0) {
		p_names = clknode_get_parent_names(clk);
		for (p_idx = 0; p_idx != clknode_get_parents_num(clk); p_idx++) {
			p_clk = clknode_find_by_name(p_names[p_idx]);
			clknode_get_freq(p_clk, &fparent);

			cur = aw_clk_nm_find_best(sc, fparent, fout, &n, &m);
			if ((*fout - cur) < (*fout - best)) {
				best = cur;
				best_parent = p_idx;
				best_n = n;
				best_m = m;
			}
		}

		p_idx = clknode_get_parent_idx(clk);
		p_clk = clknode_get_parent(clk);
		clknode_get_freq(p_clk, &fparent);
	} else {
		best = aw_clk_nm_find_best(sc, fparent, fout,
		    &best_n, &best_m);
	}

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

	if ((sc->flags & AW_CLK_REPARENT) != 0 && p_idx != best_parent)
		clknode_set_parent_by_idx(clk, best_parent);

	DEVICE_LOCK(clk);
	READ4(clk, sc->offset, &val);

	n = aw_clk_factor_get_value(&sc->n, best_n);
	m = aw_clk_factor_get_value(&sc->m, best_m);
	val &= ~sc->n.mask;
	val &= ~sc->m.mask;
	val |= n << sc->n.shift;
	val |= m << sc->m.shift;

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