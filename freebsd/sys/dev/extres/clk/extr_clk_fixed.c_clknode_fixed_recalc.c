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
struct clknode_fixed_sc {int mult; int div; int freq; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 struct clknode_fixed_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
clknode_fixed_recalc(struct clknode *clk, uint64_t *freq)
{
	struct clknode_fixed_sc *sc;

	sc = clknode_get_softc(clk);

	if ((sc->mult != 0) && (sc->div != 0))
		*freq = (*freq / sc->div) * sc->mult;
	else
		*freq = sc->freq;
	return (0);
}