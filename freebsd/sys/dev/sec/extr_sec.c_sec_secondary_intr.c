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
struct sec_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sec_primary_intr (void*) ; 

__attribute__((used)) static void
sec_secondary_intr(void *arg)
{
	struct sec_softc *sc = arg;

	device_printf(sc->sc_dev, "spurious secondary interrupt!\n");
	sec_primary_intr(arg);
}