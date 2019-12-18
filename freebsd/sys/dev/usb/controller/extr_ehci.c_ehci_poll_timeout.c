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
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  ehci_interrupt_poll (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ehci_poll_timeout(void *arg)
{
	ehci_softc_t *sc = arg;

	DPRINTFN(3, "\n");
	ehci_interrupt_poll(sc);
}