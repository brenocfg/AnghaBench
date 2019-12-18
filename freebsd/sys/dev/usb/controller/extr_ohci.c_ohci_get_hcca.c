#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ohci_hcca {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hcca_pc; } ;
struct TYPE_5__ {struct ohci_hcca* sc_hcca_p; TYPE_1__ sc_hw; } ;
typedef  TYPE_2__ ohci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ohci_hcca *
ohci_get_hcca(ohci_softc_t *sc)
{
	usb_pc_cpu_invalidate(&sc->sc_hw.hcca_pc);
	return (sc->sc_hcca_p);
}