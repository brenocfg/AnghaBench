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
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct fsl_sdhci_softc {TYPE_1__ slot; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ fsl_sdhci_r1bfix_is_wait_done (struct fsl_sdhci_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_generic_intr (TYPE_1__*) ; 

__attribute__((used)) static void
fsl_sdhci_r1bfix_func(void * arg)
{
	struct fsl_sdhci_softc *sc = arg;
	boolean_t r1bwait_done;

	mtx_lock(&sc->slot.mtx);
	r1bwait_done = fsl_sdhci_r1bfix_is_wait_done(sc);
	mtx_unlock(&sc->slot.mtx);
	if (r1bwait_done)
		sdhci_generic_intr(&sc->slot);
}