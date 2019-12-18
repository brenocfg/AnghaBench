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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4780_clk_otg_sc {int dummy; } ;
struct clknode {int dummy; } ;
struct TYPE_3__ {int freq; int /*<<< orphan*/  div_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_LOCK (struct jz4780_clk_otg_sc*) ; 
 int /*<<< orphan*/  CLK_RD_4 (struct jz4780_clk_otg_sc*,int /*<<< orphan*/ ) ; 
 int CLK_SET_DRYRUN ; 
 int /*<<< orphan*/  CLK_UNLOCK (struct jz4780_clk_otg_sc*) ; 
 int /*<<< orphan*/  CLK_WR_4 (struct jz4780_clk_otg_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_USBPCR1 ; 
 int /*<<< orphan*/  PCR_CLK_M ; 
 struct jz4780_clk_otg_sc* clknode_get_softc (struct clknode*) ; 
 int nitems (TYPE_1__*) ; 
 TYPE_1__* otg_div_table ; 

__attribute__((used)) static int
jz4780_clk_otg_set_freq(struct clknode *clk, uint64_t fin,
    uint64_t *fout, int flags, int *stop)
{
	struct jz4780_clk_otg_sc *sc;
	uint32_t reg;
	int i;

	sc = clknode_get_softc(clk);

	for (i = 0; i < nitems(otg_div_table) - 1; i++) {
		if (*fout < (otg_div_table[i].freq + otg_div_table[i + 1].freq) / 2)
			break;
	}

	*fout = otg_div_table[i].freq;

	*stop = 1;
	if (flags & CLK_SET_DRYRUN)
		return (0);

	CLK_LOCK(sc);
	reg = CLK_RD_4(sc, JZ_USBPCR1);
	/* Set the calculated values */
	reg &= ~PCR_CLK_M;
	reg |= otg_div_table[i].div_val;
	/* Initiate the change */
	CLK_WR_4(sc, JZ_USBPCR1, reg);
	CLK_UNLOCK(sc);

	return (0);
}