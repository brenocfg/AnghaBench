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
typedef  int /*<<< orphan*/  uint8_t ;
struct upgt_softc {int /*<<< orphan*/  sc_tx_inactive; scalar_t__ sc_tx_dma_buf; struct upgt_data* sc_tx_data; int /*<<< orphan*/  sc_tx_pending; int /*<<< orphan*/  sc_tx_active; } ;
struct upgt_data {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct upgt_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPGT_STAT_INC (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int UPGT_TX_MAXCOUNT ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  st_tx_inactive ; 

__attribute__((used)) static int
upgt_alloc_tx(struct upgt_softc *sc)
{
	int i;

	STAILQ_INIT(&sc->sc_tx_active);
	STAILQ_INIT(&sc->sc_tx_inactive);
	STAILQ_INIT(&sc->sc_tx_pending);

	for (i = 0; i < UPGT_TX_MAXCOUNT; i++) {
		struct upgt_data *data = &sc->sc_tx_data[i];
		data->buf = ((uint8_t *)sc->sc_tx_dma_buf) + (i * MCLBYTES);
		STAILQ_INSERT_TAIL(&sc->sc_tx_inactive, data, next);
		UPGT_STAT_INC(sc, st_tx_inactive);
	}

	return (0);
}