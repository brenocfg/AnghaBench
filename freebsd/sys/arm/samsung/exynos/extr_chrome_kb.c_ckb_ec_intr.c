#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kc_arg; int /*<<< orphan*/  (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ kb_callback; } ;
struct ckb_softc {int sc_flags; TYPE_2__ sc_kbd; int /*<<< orphan*/  cols; int /*<<< orphan*/  scan; } ;

/* Variables and functions */
 int CKB_FLAG_POLLING ; 
 int /*<<< orphan*/  EC_CMD_MKBP_STATE ; 
 int /*<<< orphan*/  KBDIO_KEYINPUT ; 
 int /*<<< orphan*/  ec_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ckb_ec_intr(void *arg)
{
	struct ckb_softc *sc;

	sc = arg;

	if (sc->sc_flags & CKB_FLAG_POLLING)
		return;

	ec_command(EC_CMD_MKBP_STATE, sc->scan, sc->cols,
	    sc->scan, sc->cols);

	(sc->sc_kbd.kb_callback.kc_func) (&sc->sc_kbd, KBDIO_KEYINPUT,
	    sc->sc_kbd.kb_callback.kc_arg);
}