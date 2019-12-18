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
typedef  int /*<<< orphan*/  ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  ehci_hcreset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ehci_suspend(ehci_softc_t *sc)
{
	DPRINTF("stopping the HC\n");

	/* reset HC */
	ehci_hcreset(sc);
}