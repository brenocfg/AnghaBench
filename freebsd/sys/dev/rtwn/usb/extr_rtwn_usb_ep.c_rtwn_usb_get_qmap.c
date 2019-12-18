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
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_usb_softc {int ntx; } ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_TRXDMA_CTRL_QMAP_3EP ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL_QMAP_HQ ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL_QMAP_HQ_NQ ; 
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 

uint16_t
rtwn_usb_get_qmap(struct rtwn_softc *sc)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);

	switch (uc->ntx) {
	case 1:
		return (R92C_TRXDMA_CTRL_QMAP_HQ);
	case 2:
		return (R92C_TRXDMA_CTRL_QMAP_HQ_NQ);
	default:
		return (R92C_TRXDMA_CTRL_QMAP_3EP);
	}
}