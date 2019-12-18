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
struct vtnet_softc {int /*<<< orphan*/  vtnet_dev; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 

__attribute__((used)) static int
vtnet_tunable_int(struct vtnet_softc *sc, const char *knob, int def)
{
	char path[64];

	snprintf(path, sizeof(path),
	    "hw.vtnet.%d.%s", device_get_unit(sc->vtnet_dev), knob);
	TUNABLE_INT_FETCH(path, &def);

	return (def);
}