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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  struct qman_softc* t_Handle ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
struct qman_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  e_RxStoreResponse ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e_RX_STORE_RESPONSE_CONTINUE ; 

e_RxStoreResponse
qman_received_frame_callback(t_Handle app, t_Handle qm_fqr, t_Handle qm_portal,
    uint32_t fqid_offset, t_DpaaFD *frame)
{
	struct qman_softc *sc;

	sc = app;

	device_printf(sc->sc_dev, "dummy callback for received frame.\n");
	return (e_RX_STORE_RESPONSE_CONTINUE);
}