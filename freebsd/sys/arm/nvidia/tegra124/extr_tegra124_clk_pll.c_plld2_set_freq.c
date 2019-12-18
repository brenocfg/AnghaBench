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
struct mnp_bits {int m_width; int n_width; } ;
struct pll_sc {struct pdiv_table* pdiv_table; struct mnp_bits mnp_bits; } ;
struct pdiv_table {scalar_t__ divider; } ;
typedef  int int64_t ;

/* Variables and functions */
 int CLK_SET_DRYRUN ; 
 int ERANGE ; 
 int INT64_MAX ; 
 int PLLD2_PFD_MAX ; 
 int PLLD2_PFD_MIN ; 
 int PLLD2_VCO_MAX ; 
 int PLLD2_VCO_MIN ; 
 int pll_set_std (struct pll_sc*,int,int*,int,int,int,int) ; 

__attribute__((used)) static int
plld2_set_freq(struct pll_sc *sc, uint64_t fin, uint64_t *fout, int flags)
{
	uint32_t m, n, p;
	uint32_t best_m, best_n, best_p;
	uint64_t vco, pfd;
	int64_t err, best_err;
	struct mnp_bits *mnp_bits;
	struct pdiv_table *tbl;
	int p_idx, rv;

	mnp_bits = &sc->mnp_bits;
	tbl = sc->pdiv_table;
	best_err = INT64_MAX;

	for (p_idx = 0; tbl[p_idx].divider != 0; p_idx++) {
		p = tbl[p_idx].divider;

		/* Check constraints */
		vco = *fout * p;
		if (vco < PLLD2_VCO_MIN)
			continue;
		if (vco > PLLD2_VCO_MAX)
			break;

		for (m = 1; m < (1 << mnp_bits->m_width); m++) {
			n = (*fout * p * m + fin / 2) / fin;

			/* Check constraints */
			if (n == 0)
				continue;
			if (n >= (1 << mnp_bits->n_width))
				break;
			vco = (fin * n) / m;
			if (vco > PLLD2_VCO_MAX || vco < PLLD2_VCO_MIN)
				continue;
			pfd = fin / m;
			if (pfd > PLLD2_PFD_MAX || vco < PLLD2_PFD_MIN)
				continue;

			/* Constraints passed, save best result */
			err = *fout - vco / p;
			if (err < 0)
				err = -err;
			if (err < best_err) {
				best_err = err;
				best_p = p;
				best_m = m;
				best_n = n;
			}
			if (err == 0)
				goto done;
		}
	}
done:
	/*
	 * HDMI specification allows 5% pixel clock tolerance,
	 * we will by a slightly stricter
	 */
	if (best_err > ((*fout * 100) / 4))
		return (ERANGE);

	if (flags & CLK_SET_DRYRUN)
		return (0);
	rv = pll_set_std(sc, fin, fout, flags, best_m, best_n, best_p);
	/* XXXX Panic for rv == ERANGE ? */
	return (rv);
}