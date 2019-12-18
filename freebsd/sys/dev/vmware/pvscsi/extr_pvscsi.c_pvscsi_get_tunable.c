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
struct pvscsi_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

__attribute__((used)) static int pvscsi_get_tunable(struct pvscsi_softc *sc, char *name, int value)
{
	char cfg[64];

	snprintf(cfg, sizeof(cfg), "hw.pvscsi.%d.%s", device_get_unit(sc->dev),
	    name);
	TUNABLE_INT_FETCH(cfg, &value);

	return (value);
}