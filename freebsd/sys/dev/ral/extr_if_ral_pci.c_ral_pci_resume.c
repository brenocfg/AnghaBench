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
struct ral_pci_softc {TYPE_1__* sc_opns; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct ral_pci_softc*) ;} ;

/* Variables and functions */
 struct ral_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ral_pci_softc*) ; 

__attribute__((used)) static int
ral_pci_resume(device_t dev)
{
	struct ral_pci_softc *psc = device_get_softc(dev);

	(*psc->sc_opns->resume)(psc);

	return 0;
}