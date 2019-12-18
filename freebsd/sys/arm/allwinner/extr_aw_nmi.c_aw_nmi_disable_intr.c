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
struct intr_irqsrc {int dummy; } ;
struct aw_nmi_softc {TYPE_1__* cfg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_IRQ_ENABLE ; 
 int /*<<< orphan*/  SC_NMI_WRITE (struct aw_nmi_softc*,int /*<<< orphan*/ ,int) ; 
 struct aw_nmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aw_nmi_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct aw_nmi_softc *sc;

	sc = device_get_softc(dev);

	SC_NMI_WRITE(sc, sc->cfg->enable_reg, !NMI_IRQ_ENABLE);
}