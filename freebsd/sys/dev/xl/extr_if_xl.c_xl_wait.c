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
struct xl_softc {int /*<<< orphan*/  xl_dev; } ;

/* Variables and functions */
 int CSR_READ_2 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XL_STATUS ; 
 int XL_STAT_CMDBUSY ; 
 int XL_TIMEOUT ; 
 scalar_t__ bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xl_wait(struct xl_softc *sc)
{
	int			i;

	for (i = 0; i < XL_TIMEOUT; i++) {
		if ((CSR_READ_2(sc, XL_STATUS) & XL_STAT_CMDBUSY) == 0)
			break;
	}

	if (i == XL_TIMEOUT && bus_child_present(sc->xl_dev))
		device_printf(sc->xl_dev, "command never completed!\n");
}