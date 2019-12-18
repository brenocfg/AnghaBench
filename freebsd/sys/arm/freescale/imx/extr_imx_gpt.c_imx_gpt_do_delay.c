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
struct imx_gpt_softc {int clkfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_GPT_CNT ; 
 int READ4 (struct imx_gpt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
imx_gpt_do_delay(int usec, void *arg)
{
	struct imx_gpt_softc *sc = arg;
	uint64_t curcnt, endcnt, startcnt, ticks;

	/*
	 * Calculate the tick count with 64-bit values so that it works for any
	 * clock frequency.  Loop until the hardware count reaches start+ticks.
	 * If the 32-bit hardware count rolls over while we're looping, just
	 * manually do a carry into the high bits after each read; don't worry
	 * that doing this on each loop iteration is inefficient -- we're trying
	 * to waste time here.
	 */
	ticks = 1 + ((uint64_t)usec * sc->clkfreq) / 1000000;
	curcnt = startcnt = READ4(sc, IMX_GPT_CNT);
	endcnt = startcnt + ticks;
	while (curcnt < endcnt) {
		curcnt = READ4(sc, IMX_GPT_CNT);
		if (curcnt < startcnt)
			curcnt += 1ULL << 32;
	}
}