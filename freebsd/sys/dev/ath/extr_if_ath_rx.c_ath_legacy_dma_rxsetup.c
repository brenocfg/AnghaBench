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
struct ath_softc {int /*<<< orphan*/  sc_rxbuf; int /*<<< orphan*/  sc_rxdma; } ;
struct ath_desc {int dummy; } ;

/* Variables and functions */
 int ath_descdma_setup (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_rxbuf ; 

__attribute__((used)) static int
ath_legacy_dma_rxsetup(struct ath_softc *sc)
{
	int error;

	error = ath_descdma_setup(sc, &sc->sc_rxdma, &sc->sc_rxbuf,
	    "rx", sizeof(struct ath_desc), ath_rxbuf, 1);
	if (error != 0)
		return (error);

	return (0);
}