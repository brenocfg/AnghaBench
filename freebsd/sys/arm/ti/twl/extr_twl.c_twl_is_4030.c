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
struct twl_softc {scalar_t__ sc_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ TWL_DEVICE_4030 ; 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
twl_is_4030(device_t dev)
{
	struct twl_softc *sc = device_get_softc(dev);
	return (sc->sc_type == TWL_DEVICE_4030);
}