#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  si_note; } ;
struct beri_softc {int /*<<< orphan*/  beri_mtx; TYPE_3__ beri_rsel; } ;
struct TYPE_5__ {int cdes; } ;
typedef  TYPE_1__ control_reg_t ;

/* Variables and functions */
 int CDES_INT_EN ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PZERO ; 
 TYPE_1__ get_control_reg (struct beri_softc*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  set_control_reg (struct beri_softc*,int,TYPE_1__*) ; 

__attribute__((used)) static void
beri_intr_write(void *arg)
{
	struct beri_softc *sc;
	control_reg_t c;

	sc = arg;

	c = get_control_reg(sc, 1);
	if (c.cdes & CDES_INT_EN) {
		c.cdes &= ~(CDES_INT_EN);
		set_control_reg(sc, 1, &c);
	}

	mtx_lock(&sc->beri_mtx);
	selwakeuppri(&sc->beri_rsel, PZERO + 1);
	KNOTE_LOCKED(&sc->beri_rsel.si_note, 0);
	mtx_unlock(&sc->beri_mtx);
}