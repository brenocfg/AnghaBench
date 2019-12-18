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
struct aic_softc {int /*<<< orphan*/  xchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICCR ; 
 int AICCR_ERPL ; 
 int AICCR_TDMS ; 
 int READ4 (struct aic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct aic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XDMA_CMD_TERMINATE ; 
 int /*<<< orphan*/  xdma_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aic_stop(struct sc_pcminfo *scp)
{
	struct aic_softc *sc;
	int reg;

	sc = scp->sc;

	reg = READ4(sc, AICCR);
	reg &= ~(AICCR_TDMS | AICCR_ERPL);
	WRITE4(sc, AICCR, reg);

	xdma_control(sc->xchan, XDMA_CMD_TERMINATE);

	return (0);
}