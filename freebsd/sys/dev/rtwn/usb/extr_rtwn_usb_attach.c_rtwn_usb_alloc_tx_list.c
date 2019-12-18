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
struct rtwn_usb_softc {int /*<<< orphan*/ * uc_tx; int /*<<< orphan*/  uc_tx_inactive; int /*<<< orphan*/  uc_tx_pending; int /*<<< orphan*/  uc_tx_active; } ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_USB_TXBUFSZ ; 
 int RTWN_USB_TX_LIST_COUNT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int rtwn_usb_alloc_list (struct rtwn_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_usb_alloc_tx_list(struct rtwn_softc *sc)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);
	int error, i;

	error = rtwn_usb_alloc_list(sc, uc->uc_tx, RTWN_USB_TX_LIST_COUNT,
	    RTWN_USB_TXBUFSZ);
	if (error != 0)
		return (error);

	STAILQ_INIT(&uc->uc_tx_active);
	STAILQ_INIT(&uc->uc_tx_inactive);
	STAILQ_INIT(&uc->uc_tx_pending);

	for (i = 0; i < RTWN_USB_TX_LIST_COUNT; i++)
		STAILQ_INSERT_HEAD(&uc->uc_tx_inactive, &uc->uc_tx[i], next);

	return (0);
}