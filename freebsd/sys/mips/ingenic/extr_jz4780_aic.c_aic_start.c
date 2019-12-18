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
struct sc_pcminfo {struct aic_softc* sc; } ;
struct aic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICCR ; 
 int AICCR_CHANNEL_2 ; 
 int AICCR_ERPL ; 
 int AICCR_ISS_16 ; 
 int AICCR_OSS_16 ; 
 int AICCR_TDMS ; 
 int /*<<< orphan*/  I2SCR ; 
 int I2SCR_ESCLK ; 
 int READ4 (struct aic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct aic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_xdma (struct sc_pcminfo*) ; 

__attribute__((used)) static int
aic_start(struct sc_pcminfo *scp)
{
	struct aic_softc *sc;
	int reg;

	sc = scp->sc;

	/* Ensure clock enabled. */
	reg = READ4(sc, I2SCR);
	reg |= (I2SCR_ESCLK);
	WRITE4(sc, I2SCR, reg);

	setup_xdma(scp);

	reg = (AICCR_OSS_16 | AICCR_ISS_16);
	reg |= (AICCR_CHANNEL_2);
	reg |= (AICCR_TDMS);
	reg |= (AICCR_ERPL);
	WRITE4(sc, AICCR, reg);

	return (0);
}