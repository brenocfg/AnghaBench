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
struct TYPE_2__ {int va_flags; } ;
struct creator_softc {int sc_node; TYPE_1__ sc_va; int /*<<< orphan*/ ** sc_bt; int /*<<< orphan*/ * sc_bh; int /*<<< orphan*/  sc_flags; } ;
typedef  int /*<<< orphan*/  stdout ;
typedef  int phandle_t ;
typedef  char ihandle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CREATOR_AFB ; 
 int /*<<< orphan*/  CREATOR_CONSOLE ; 
 int /*<<< orphan*/  CREATOR_DRIVER_NAME ; 
 int FFB_DAC ; 
 int FFB_FBC ; 
 scalar_t__ OF_decode_addr (int,int,int*,int /*<<< orphan*/ *) ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int OF_instance_to_package (char) ; 
 int VIO_PROBE_ONLY ; 
 int V_ADP_REGISTERED ; 
 int /*<<< orphan*/ * creator_bst_store ; 
 scalar_t__ creator_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct creator_softc creator_softc ; 
 int /*<<< orphan*/  sparc64_fake_bustag (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ vid_find_adapter (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
creator_configure(int flags)
{
	struct creator_softc *sc;
	phandle_t chosen;
	phandle_t output;
	ihandle_t stdout;
	bus_addr_t addr;
	char buf[sizeof("SUNW,ffb")];
	int i;
	int space;

	/*
	 * For the high-level console probing return the number of
	 * registered adapters.
	 */
	if (!(flags & VIO_PROBE_ONLY)) {
		for (i = 0; vid_find_adapter(CREATOR_DRIVER_NAME, i) >= 0; i++)
			;
		return (i);
	}

	/* Low-level console probing and initialization. */

	sc = &creator_softc;
	if (sc->sc_va.va_flags & V_ADP_REGISTERED)
		goto found;

	if ((chosen = OF_finddevice("/chosen")) == -1)
		return (0);
	if (OF_getprop(chosen, "stdout", &stdout, sizeof(stdout)) == -1)
		return (0);
	if ((output = OF_instance_to_package(stdout)) == -1)
		return (0);
	if (OF_getprop(output, "name", buf, sizeof(buf)) == -1)
		return (0);
	if (strcmp(buf, "SUNW,ffb") == 0 || strcmp(buf, "SUNW,afb") == 0) {
		sc->sc_flags = CREATOR_CONSOLE;
		if (strcmp(buf, "SUNW,afb") == 0)
			sc->sc_flags |= CREATOR_AFB;
		sc->sc_node = output;
	} else
		return (0);

	for (i = FFB_DAC; i <= FFB_FBC; i++) {
		if (OF_decode_addr(output, i, &space, &addr) != 0)
			return (0);
		sc->sc_bt[i] = &creator_bst_store[i - FFB_DAC];
		sc->sc_bh[i] = sparc64_fake_bustag(space, addr, sc->sc_bt[i]);
	}

	if (creator_init(0, &sc->sc_va, 0) < 0)
		return (0);

 found:
	/* Return number of found adapters. */
	return (1);
}