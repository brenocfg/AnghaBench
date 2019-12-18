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
 int ERANGE ; 
 struct clknode_fixed_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
clknode_fixed_set_freq(struct clknode *clk, uint64_t fin, uint64_t *fout,
    int flags, int *stop)
{
	struct clknode_fixed_sc *sc;

	sc = clknode_get_softc(clk);
	if (sc->mult == 0 || sc->div == 0) {
		/* Fixed frequency clock. */
		*stop = 1;
		if (*fout != sc->freq)
			return (ERANGE);
		return (0);
	}
	/* Fixed factor clock. */
	*stop = 0;
	*fout = (*fout / sc->mult) *  sc->div;
	return (0);
}