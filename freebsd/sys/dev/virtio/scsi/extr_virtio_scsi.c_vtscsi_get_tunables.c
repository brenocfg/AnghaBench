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
typedef  int /*<<< orphan*/  tmpstr ;
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_debug; int /*<<< orphan*/  vtscsi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
vtscsi_get_tunables(struct vtscsi_softc *sc)
{
	char tmpstr[64];

	TUNABLE_INT_FETCH("hw.vtscsi.debug_level", &sc->vtscsi_debug);

	snprintf(tmpstr, sizeof(tmpstr), "dev.vtscsi.%d.debug_level",
	    device_get_unit(sc->vtscsi_dev));
	TUNABLE_INT_FETCH(tmpstr, &sc->vtscsi_debug);
}