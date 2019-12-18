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
struct ukbd_softc {int sc_flags; scalar_t__ sc_inputs; int* sc_input; size_t sc_inputhead; int /*<<< orphan*/ * sc_xfer; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int UKBD_FLAG_GONE ; 
 int UKBD_FLAG_POLLING ; 
 size_t UKBD_INTR_DT_0 ; 
 size_t UKBD_INTR_DT_1 ; 
 size_t UKBD_IN_BUF_SIZE ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 scalar_t__ USB_IN_POLLING_MODE_FUNC () ; 
 int /*<<< orphan*/  ukbd_do_poll (struct ukbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ukbd_get_key(struct ukbd_softc *sc, uint8_t wait)
{
	int32_t c;

	UKBD_LOCK_ASSERT();
	KASSERT((USB_IN_POLLING_MODE_FUNC() == 0) ||
	    (sc->sc_flags & UKBD_FLAG_POLLING) != 0,
	    ("not polling in kdb or panic\n"));

	if (sc->sc_inputs == 0 &&
	    (sc->sc_flags & UKBD_FLAG_GONE) == 0) {
		/* start transfer, if not already started */
		usbd_transfer_start(sc->sc_xfer[UKBD_INTR_DT_0]);
		usbd_transfer_start(sc->sc_xfer[UKBD_INTR_DT_1]);
	}

	if (sc->sc_flags & UKBD_FLAG_POLLING)
		ukbd_do_poll(sc, wait);

	if (sc->sc_inputs == 0) {
		c = -1;
	} else {
		c = sc->sc_input[sc->sc_inputhead];
		--(sc->sc_inputs);
		++(sc->sc_inputhead);
		if (sc->sc_inputhead >= UKBD_IN_BUF_SIZE) {
			sc->sc_inputhead = 0;
		}
	}
	return (c);
}