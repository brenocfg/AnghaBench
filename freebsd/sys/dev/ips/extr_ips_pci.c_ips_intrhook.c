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
struct ips_softc {int configured; int /*<<< orphan*/  ips_ich; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 scalar_t__ ips_adapter_init (struct ips_softc*) ; 
 int /*<<< orphan*/  ips_pci_free (struct ips_softc*) ; 

__attribute__((used)) static void
ips_intrhook(void *arg)
{
	struct ips_softc *sc = (struct ips_softc *)arg;

	config_intrhook_disestablish(&sc->ips_ich);
	if (ips_adapter_init(sc))
		ips_pci_free(sc);
	else
		sc->configured = 1;
}