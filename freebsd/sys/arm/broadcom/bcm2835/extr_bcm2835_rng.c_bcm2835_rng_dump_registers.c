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
typedef  int uint32_t ;
struct sbuf {int dummy; } ;
struct bcm2835_rng_softc {int dummy; } ;

/* Variables and functions */
 int RND_VAL_MASK ; 
 int RND_VAL_SHIFT ; 
 int RND_WARM_CNT ; 
 int RNG_COMBLK1_OSC ; 
 int RNG_COMBLK1_OSC_SHIFT ; 
 int RNG_COMBLK2_OSC ; 
 int RNG_COMBLK2_OSC_SHIFT ; 
 int /*<<< orphan*/  RNG_CTRL ; 
 int /*<<< orphan*/  RNG_FF_THRES ; 
 int RNG_FF_THRES_MASK ; 
 int /*<<< orphan*/  RNG_INT_MASK ; 
 int RNG_INT_OFF_BIT ; 
 int RNG_JCLK_BYP_DIV_CNT ; 
 int RNG_JCLK_BYP_DIV_CNT_SHIFT ; 
 int RNG_JCLK_BYP_SEL ; 
 int RNG_JCLK_BYP_SRC ; 
 int RNG_NUM_OSCILLATORS ; 
 int RNG_RBG2X ; 
 int RNG_RBGEN_BIT ; 
 int /*<<< orphan*/  RNG_STATUS ; 
 int bcm2835_rng_read4 (struct bcm2835_rng_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
bcm2835_rng_dump_registers(struct bcm2835_rng_softc *sc, struct sbuf *sbp)
{
	uint32_t comblk2_osc, comblk1_osc, jclk_byp_div, val;
	int i;

	/* Display RNG control register contents */
	val = bcm2835_rng_read4(sc, RNG_CTRL);
	sbuf_printf(sbp, "RNG_CTRL (%08x)\n", val);

	comblk2_osc = (val & RNG_COMBLK2_OSC) >> RNG_COMBLK2_OSC_SHIFT;
	sbuf_printf(sbp, "  RNG_COMBLK2_OSC (%02x)\n", comblk2_osc);
	for (i = 0; i < RNG_NUM_OSCILLATORS; i++)
		if ((comblk2_osc & (1 << i)) == 0)
			sbuf_printf(sbp, "    Oscillator %d enabled\n", i + 1);

	comblk1_osc = (val & RNG_COMBLK1_OSC) >> RNG_COMBLK1_OSC_SHIFT;
	sbuf_printf(sbp, "  RNG_COMBLK1_OSC (%02x)\n", comblk1_osc);
	for (i = 0; i < RNG_NUM_OSCILLATORS; i++)
		if ((comblk1_osc & (1 << i)) == 0)
			sbuf_printf(sbp, "    Oscillator %d enabled\n", i + 1);

	jclk_byp_div = (val & RNG_JCLK_BYP_DIV_CNT) >>
	    RNG_JCLK_BYP_DIV_CNT_SHIFT;
	sbuf_printf(sbp,
	    "  RNG_JCLK_BYP_DIV_CNT (%02x)\n    APB clock frequency / %d\n",
	    jclk_byp_div, 2 * (jclk_byp_div + 1));

	sbuf_printf(sbp, "  RNG_JCLK_BYP_SRC:\n    %s\n",
	    (val & RNG_JCLK_BYP_SRC) ? "Use divided down APB clock" :
	    "Use RNG clock (APB clock)");

	sbuf_printf(sbp, "  RNG_JCLK_BYP_SEL:\n    %s\n",
	    (val & RNG_JCLK_BYP_SEL) ? "Bypass internal jitter clock" :
	    "Use internal jitter clock");

	if ((val & RNG_RBG2X) != 0)
		sbuf_cat(sbp, "  RNG_RBG2X: RNG 2X SPEED enabled\n");

	if ((val & RNG_RBGEN_BIT) != 0)
		sbuf_cat(sbp, "  RNG_RBGEN_BIT: RBG enabled\n");

	/* Display RNG status register contents */
	val = bcm2835_rng_read4(sc, RNG_STATUS);
	sbuf_printf(sbp, "RNG_CTRL (%08x)\n", val);
	sbuf_printf(sbp, "  RND_VAL: %02x\n",
	    (val >> RND_VAL_SHIFT) & RND_VAL_MASK);
	sbuf_printf(sbp, "  RND_WARM_CNT: %05x\n", val & RND_WARM_CNT);

	/* Display FIFO threshold register contents */
	val = bcm2835_rng_read4(sc, RNG_FF_THRES);
	sbuf_printf(sbp, "RNG_FF_THRES: %05x\n", val & RNG_FF_THRES_MASK);

	/* Display interrupt mask register contents */
	val = bcm2835_rng_read4(sc, RNG_INT_MASK);
	sbuf_printf(sbp, "RNG_INT_MASK: interrupt %s\n",
	     ((val & RNG_INT_OFF_BIT) != 0) ? "disabled" : "enabled");
}