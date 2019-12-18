#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ucom_softc {int sc_flag; TYPE_1__* sc_line_state_task; int /*<<< orphan*/  sc_pls_clr; int /*<<< orphan*/  sc_pls_set; int /*<<< orphan*/  sc_pls_curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UCOM_FLAG_HL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_cfg_line_state ; 
 int /*<<< orphan*/  ucom_queue_command (struct ucom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ucom_line_state(struct ucom_softc *sc,
    uint8_t set_bits, uint8_t clear_bits)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}

	DPRINTF("on=0x%02x, off=0x%02x\n", set_bits, clear_bits);

	/* update current programmed line state */
	sc->sc_pls_curr |= set_bits;
	sc->sc_pls_curr &= ~clear_bits;
	sc->sc_pls_set |= set_bits;
	sc->sc_pls_clr |= clear_bits;

	/* defer driver programming */
	ucom_queue_command(sc, ucom_cfg_line_state, NULL,
	    &sc->sc_line_state_task[0].hdr, 
	    &sc->sc_line_state_task[1].hdr);
}