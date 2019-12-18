#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kc_arg; int /*<<< orphan*/  (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ kb_callback; } ;
struct ckb_softc {int sc_repeat_key; int sc_repeating; TYPE_2__ sc_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBDIO_KEYINPUT ; 
 scalar_t__ KBD_IS_ACTIVE (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ckb_repeat(void *arg)
{
	struct ckb_softc *sc;

	sc = arg;

	if (KBD_IS_ACTIVE(&sc->sc_kbd) && KBD_IS_BUSY(&sc->sc_kbd)) {
		if (sc->sc_repeat_key != -1) {
			sc->sc_repeating = 1;
			sc->sc_kbd.kb_callback.kc_func(&sc->sc_kbd,
			    KBDIO_KEYINPUT, sc->sc_kbd.kb_callback.kc_arg);
		}
	}
}