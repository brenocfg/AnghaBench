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
struct pci_nvme_softc {int /*<<< orphan*/  fw_log; int /*<<< orphan*/  health_log; int /*<<< orphan*/  err_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_nvme_init_logpages(struct pci_nvme_softc *sc)
{

	memset(&sc->err_log, 0, sizeof(sc->err_log));
	memset(&sc->health_log, 0, sizeof(sc->health_log));
	memset(&sc->fw_log, 0, sizeof(sc->fw_log));
}