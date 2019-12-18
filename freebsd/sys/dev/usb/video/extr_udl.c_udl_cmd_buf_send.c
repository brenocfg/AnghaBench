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
struct udl_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_cmd_buf_pending; int /*<<< orphan*/  sc_cmd_buf_free; scalar_t__ sc_gone; } ;
struct udl_cmd_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDL_BULK_CMD_EOC ; 
 int /*<<< orphan*/  UDL_BULK_SOC ; 
 size_t UDL_BULK_WRITE_0 ; 
 size_t UDL_BULK_WRITE_1 ; 
 int /*<<< orphan*/  UDL_LOCK (struct udl_softc*) ; 
 int /*<<< orphan*/  UDL_UNLOCK (struct udl_softc*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  udl_cmd_insert_int_1 (struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
udl_cmd_buf_send(struct udl_softc *sc, struct udl_cmd_buf *cb)
{
	UDL_LOCK(sc);
	if (sc->sc_gone) {
		TAILQ_INSERT_TAIL(&sc->sc_cmd_buf_free, cb, entry);
	} else {
		/* mark end of command stack */
		udl_cmd_insert_int_1(cb, UDL_BULK_SOC);
		udl_cmd_insert_int_1(cb, UDL_BULK_CMD_EOC);

		TAILQ_INSERT_TAIL(&sc->sc_cmd_buf_pending, cb, entry);
		usbd_transfer_start(sc->sc_xfer[UDL_BULK_WRITE_0]);
		usbd_transfer_start(sc->sc_xfer[UDL_BULK_WRITE_1]);
	}
	UDL_UNLOCK(sc);
}