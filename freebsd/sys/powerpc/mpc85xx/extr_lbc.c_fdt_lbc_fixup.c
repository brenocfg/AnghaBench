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
typedef  int /*<<< orphan*/  width ;
struct lbc_softc {TYPE_1__* sc_banks; } ;
struct lbc_devinfo {int di_bank; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
struct TYPE_2__ {scalar_t__ size; int width; } ;

/* Variables and functions */
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,void*,int) ; 

__attribute__((used)) static void
fdt_lbc_fixup(phandle_t node, struct lbc_softc *sc, struct lbc_devinfo *di)
{
	pcell_t width;
	int bank;

	if (OF_getprop(node, "bank-width", (void *)&width, sizeof(width)) <= 0)
		return;

	bank = di->di_bank;
	if (sc->sc_banks[bank].size == 0)
		return;

	/* Express width in bits. */
	sc->sc_banks[bank].width = width * 8;
}