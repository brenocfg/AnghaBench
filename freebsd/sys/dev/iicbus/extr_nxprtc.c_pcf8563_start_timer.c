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
 int PCF8563_B_TMR_64HZ ; 
 int PCF8563_B_TMR_ENABLE ; 
 int PCF8563_M_TMR_CTRL ; 
 int /*<<< orphan*/  PCF8563_R_TMR_CTRL ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcf8563_start_timer(struct nxprtc_softc *sc)
{
	int err;
	uint8_t stdctl, tmrctl;

	/* See comment in pcf8523_start_timer().  */
	if ((err = read_reg(sc, PCF8563_R_TMR_CTRL, &tmrctl)) != 0)
		return (err);

	stdctl = PCF8563_B_TMR_ENABLE | PCF8563_B_TMR_64HZ;

	if ((tmrctl & PCF8563_M_TMR_CTRL) != stdctl) {
		if ((err = write_reg(sc, sc->tmcaddr, 0)) != 0)
			return (err);
		if ((err = write_reg(sc, PCF8563_R_TMR_CTRL, stdctl)) != 0)
			return (err);
	}
	return (0);
}