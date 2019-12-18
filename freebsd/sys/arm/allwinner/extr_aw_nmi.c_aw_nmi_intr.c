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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  isrc; } ;
struct aw_nmi_softc {int /*<<< orphan*/  dev; TYPE_2__* cfg; TYPE_1__ intr; } ;
struct TYPE_6__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_5__ {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  pending_reg; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  NMI_IRQ_ENABLE ; 
 scalar_t__ SC_NMI_READ (struct aw_nmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_NMI_WRITE (struct aw_nmi_softc*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_nmi_intr(void *arg)
{
	struct aw_nmi_softc *sc;

	sc = arg;

	if (SC_NMI_READ(sc, sc->cfg->pending_reg) == 0) {
		device_printf(sc->dev, "Spurious interrupt\n");
		return (FILTER_HANDLED);
	}

	if (intr_isrc_dispatch(&sc->intr.isrc, curthread->td_intr_frame) != 0) {
		SC_NMI_WRITE(sc, sc->cfg->enable_reg, !NMI_IRQ_ENABLE);
		device_printf(sc->dev, "Stray interrupt, NMI disabled\n");
	}

	return (FILTER_HANDLED);
}