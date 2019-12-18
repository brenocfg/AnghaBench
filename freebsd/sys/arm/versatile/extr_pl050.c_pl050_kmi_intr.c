#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  kc_arg; int /*<<< orphan*/  (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ kb_callback; } ;
struct kmi_softc {int sc_flags; TYPE_2__ sc_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBDIO_KEYINPUT ; 
 scalar_t__ KBD_IS_ACTIVE (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  KMI_CTX_LOCK_ASSERT () ; 
 int KMI_FLAG_POLLING ; 
 scalar_t__ NOKEY ; 
 scalar_t__ kmi_read_char_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pl050_kmi_intr(void *arg)
{
	struct kmi_softc *sc = arg;
	uint32_t c;

	KMI_CTX_LOCK_ASSERT();

	if ((sc->sc_flags & KMI_FLAG_POLLING) != 0)
		return;

	if (KBD_IS_ACTIVE(&sc->sc_kbd) &&
	    KBD_IS_BUSY(&sc->sc_kbd)) {
		/* let the callback function process the input */
		(sc->sc_kbd.kb_callback.kc_func) (&sc->sc_kbd, KBDIO_KEYINPUT,
		    sc->sc_kbd.kb_callback.kc_arg);
	} else {
		/* read and discard the input, no one is waiting for it */
		do {
			c = kmi_read_char_locked(&sc->sc_kbd, 0);
		} while (c != NOKEY);
	}

}