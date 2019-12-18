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
typedef  int /*<<< orphan*/  uint32_t ;
struct mnp_bits {int /*<<< orphan*/  p_width; int /*<<< orphan*/  p_shift; int /*<<< orphan*/  n_width; int /*<<< orphan*/  m_width; } ;
struct pll_sc {int /*<<< orphan*/  base_reg; struct mnp_bits mnp_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_BASE_DIVM_SHIFT ; 
 int /*<<< orphan*/  PLL_BASE_DIVN_SHIFT ; 
 int /*<<< orphan*/  RD4 (struct pll_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_divisors(struct pll_sc *sc, uint32_t *m, uint32_t *n, uint32_t *p)
{
	uint32_t val;
	struct mnp_bits *mnp_bits;

	mnp_bits = &sc->mnp_bits;
	RD4(sc, sc->base_reg, &val);
	*m = get_masked(val, PLL_BASE_DIVM_SHIFT, mnp_bits->m_width);
	*n = get_masked(val, PLL_BASE_DIVN_SHIFT, mnp_bits->n_width);
	*p = get_masked(val, mnp_bits->p_shift, mnp_bits->p_width);
}