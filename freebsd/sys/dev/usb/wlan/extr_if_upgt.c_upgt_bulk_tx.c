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
struct upgt_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_tx_pending; } ;
struct upgt_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct upgt_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPGT_ASSERT_LOCKED (struct upgt_softc*) ; 
 size_t UPGT_BULK_TX ; 
 int /*<<< orphan*/  UPGT_STAT_INC (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  st_tx_pending ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_bulk_tx(struct upgt_softc *sc, struct upgt_data *data)
{

	UPGT_ASSERT_LOCKED(sc);

	STAILQ_INSERT_TAIL(&sc->sc_tx_pending, data, next);
	UPGT_STAT_INC(sc, st_tx_pending);
	usbd_transfer_start(sc->sc_xfer[UPGT_BULK_TX]);
}