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
struct TYPE_2__ {int /*<<< orphan*/  lsc; } ;
struct le_pci_softc {TYPE_1__ sc_am79900; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct le_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lance_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
le_pci_resume(device_t dev)
{
	struct le_pci_softc *lesc;

	lesc = device_get_softc(dev);

	lance_resume(&lesc->sc_am79900.lsc);

	return (0);
}