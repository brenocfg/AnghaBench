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
struct vtpci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtpci_free_interrupts (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_free_virtqueues (struct vtpci_softc*) ; 

__attribute__((used)) static void
vtpci_release_child_resources(struct vtpci_softc *sc)
{

	vtpci_free_interrupts(sc);
	vtpci_free_virtqueues(sc);
}