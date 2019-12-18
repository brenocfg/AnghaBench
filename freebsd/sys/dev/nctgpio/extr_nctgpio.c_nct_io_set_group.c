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
struct nct_softc {int curgrp; int /*<<< orphan*/  iores; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_ASSERT_LOCKED (struct nct_softc*) ; 
 int /*<<< orphan*/  NCT_IO_GSR ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nct_io_set_group(struct nct_softc *sc, int group)
{

	GPIO_ASSERT_LOCKED(sc);
	if (group != sc->curgrp) {
		bus_write_1(sc->iores, NCT_IO_GSR, group);
		sc->curgrp = group;
	}
}