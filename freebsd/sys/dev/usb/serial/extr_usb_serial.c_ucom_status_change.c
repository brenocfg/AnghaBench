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
struct ucom_softc {int sc_flag; TYPE_1__* sc_status_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UCOM_FLAG_CONSOLE ; 
 int UCOM_FLAG_HL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_cfg_status_change ; 
 int /*<<< orphan*/  ucom_queue_command (struct ucom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ucom_status_change(struct ucom_softc *sc)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (sc->sc_flag & UCOM_FLAG_CONSOLE)
		return;		/* not supported */

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}
	DPRINTF("\n");

	ucom_queue_command(sc, ucom_cfg_status_change, NULL,
	    &sc->sc_status_task[0].hdr,
	    &sc->sc_status_task[1].hdr);
}