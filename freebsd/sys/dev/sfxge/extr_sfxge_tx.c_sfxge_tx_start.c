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
struct sfxge_softc {int txq_count; int /*<<< orphan*/  enp; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_tx_fini (int /*<<< orphan*/ ) ; 
 int efx_tx_init (int /*<<< orphan*/ ) ; 
 int sfxge_tx_qstart (struct sfxge_softc*,int) ; 
 int /*<<< orphan*/  sfxge_tx_qstop (struct sfxge_softc*,int) ; 

int
sfxge_tx_start(struct sfxge_softc *sc)
{
	int index;
	int rc;

	/* Initialize the common code transmit module. */
	if ((rc = efx_tx_init(sc->enp)) != 0)
		return (rc);

	for (index = 0; index < sc->txq_count; index++) {
		if ((rc = sfxge_tx_qstart(sc, index)) != 0)
			goto fail;
	}

	return (0);

fail:
	while (--index >= 0)
		sfxge_tx_qstop(sc, index);

	efx_tx_fini(sc->enp);

	return (rc);
}