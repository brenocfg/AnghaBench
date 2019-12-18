#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct psci_softc {int dummy; } ;
typedef  scalar_t__ (* psci_initfn_t ) (int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct psci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct psci_softc* psci_softc ; 

__attribute__((used)) static int
psci_attach(device_t dev, psci_initfn_t psci_init, int default_version)
{
	struct psci_softc *sc = device_get_softc(dev);

	if (psci_softc != NULL)
		return (ENXIO);

	KASSERT(psci_init != NULL, ("PSCI init function cannot be NULL"));
	if (psci_init(dev, default_version))
		return (ENXIO);

	psci_softc = sc;

	return (0);
}