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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct twsi_softc {int /*<<< orphan*/  clk_core; } ;
struct twsi_baud_rate {int m; int n; int /*<<< orphan*/  param; void* raw; } ;

/* Variables and functions */
 int ABSSUB (int const,int) ; 
 int /*<<< orphan*/  TWSI_BAUD_RATE_PARAM (int,int) ; 
 void* TWSI_BAUD_RATE_RAW (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clk_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tclk () ; 

__attribute__((used)) static void
mv_twsi_cal_baud_rate(struct twsi_softc *sc, const uint32_t target,
    struct twsi_baud_rate *rate)
{
	uint64_t clk;
	uint32_t cur, diff, diff0;
	int m, n, m0, n0;

	/* Calculate baud rate. */
	m0 = n0 = 4;	/* Default values on reset */
	diff0 = 0xffffffff;
#ifdef __aarch64__
	clk_get_freq(sc->clk_core, &clk);
#else
	clk = get_tclk();
#endif

	for (n = 0; n < 8; n++) {
		for (m = 0; m < 16; m++) {
			cur = TWSI_BAUD_RATE_RAW(clk,m,n);
			diff = ABSSUB(target, cur);
			if (diff < diff0) {
				m0 = m;
				n0 = n;
				diff0 = diff;
			}
		}
	}
	rate->raw = TWSI_BAUD_RATE_RAW(clk, m0, n0);
	rate->param = TWSI_BAUD_RATE_PARAM(m0, n0);
	rate->m = m0;
	rate->n = n0;
}