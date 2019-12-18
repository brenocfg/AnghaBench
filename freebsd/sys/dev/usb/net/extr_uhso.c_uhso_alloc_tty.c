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
struct uhso_tty {int dummy; } ;
struct uhso_softc {int sc_ttys; TYPE_1__* sc_tty; TYPE_1__* sc_ucom; } ;
struct ucom_softc {int dummy; } ;
struct TYPE_2__ {struct uhso_softc* ht_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,int) ; 
 void* reallocf (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
uhso_alloc_tty(struct uhso_softc *sc)
{

	sc->sc_ttys++;
	sc->sc_tty = reallocf(sc->sc_tty, sizeof(struct uhso_tty) * sc->sc_ttys,
	    M_USBDEV, M_WAITOK | M_ZERO);
	if (sc->sc_tty == NULL)
		return (-1);

	sc->sc_ucom = reallocf(sc->sc_ucom,
	    sizeof(struct ucom_softc) * sc->sc_ttys, M_USBDEV, M_WAITOK | M_ZERO);
	if (sc->sc_ucom == NULL)
		return (-1);

	sc->sc_tty[sc->sc_ttys - 1].ht_sc = sc;

	UHSO_DPRINTF(1, "Allocated TTY %d\n", sc->sc_ttys - 1);	
	return (sc->sc_ttys - 1);
}