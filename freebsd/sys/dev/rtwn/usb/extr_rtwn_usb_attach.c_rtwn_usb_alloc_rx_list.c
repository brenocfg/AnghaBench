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
struct rtwn_usb_softc {int uc_rx_buf_size; int /*<<< orphan*/ * uc_rx; int /*<<< orphan*/  uc_rx_inactive; int /*<<< orphan*/  uc_rx_active; } ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int RTWN_USB_RXBUFSZ_UNIT ; 
 int RTWN_USB_RX_LIST_COUNT ; 
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int rtwn_usb_alloc_list (struct rtwn_softc*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
rtwn_usb_alloc_rx_list(struct rtwn_softc *sc)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);
	int error, i;

	error = rtwn_usb_alloc_list(sc, uc->uc_rx, RTWN_USB_RX_LIST_COUNT,
	    uc->uc_rx_buf_size * RTWN_USB_RXBUFSZ_UNIT);
	if (error != 0)
		return (error);

	STAILQ_INIT(&uc->uc_rx_active);
	STAILQ_INIT(&uc->uc_rx_inactive);

	for (i = 0; i < RTWN_USB_RX_LIST_COUNT; i++)
		STAILQ_INSERT_HEAD(&uc->uc_rx_inactive, &uc->uc_rx[i], next);

	return (0);
}