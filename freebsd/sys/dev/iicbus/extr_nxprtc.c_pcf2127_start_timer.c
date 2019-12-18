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
typedef  int uint8_t ;
struct nxprtc_softc {int /*<<< orphan*/  tmcaddr; } ;

/* Variables and functions */
 int PCF2127_B_TMR_CD ; 
 int PCF2127_M_TMR_CTRL ; 
 int /*<<< orphan*/  PCF2127_R_TMR_CTL ; 
 int PCF8523_B_TMR_A_64HZ ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcf2127_start_timer(struct nxprtc_softc *sc)
{
	int err;
	uint8_t stdctl, tmrctl;

	/*
	 * Set up timer if it's not already in the mode we normally run it.  See
	 * the comment in pcf8523_start_timer() for more details.
	 *
	 * Note that the PCF2129 datasheet says it has no countdown timer, but
	 * empirical testing shows that it works just fine for our purposes.
	 */
	if ((err = read_reg(sc, PCF2127_R_TMR_CTL, &tmrctl)) != 0)
		return (err);

	stdctl = PCF2127_B_TMR_CD | PCF8523_B_TMR_A_64HZ;

	if ((tmrctl & PCF2127_M_TMR_CTRL) != stdctl) {
		if ((err = write_reg(sc, sc->tmcaddr, 0)) != 0)
			return (err);
		if ((err = write_reg(sc, PCF2127_R_TMR_CTL, stdctl)) != 0)
			return (err);
	}
	return (0);
}