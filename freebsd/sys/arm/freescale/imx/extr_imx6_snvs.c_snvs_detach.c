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
struct snvs_softc {int /*<<< orphan*/  memres; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_unregister (int /*<<< orphan*/ ) ; 
 struct snvs_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snvs_detach(device_t dev)
{
	struct snvs_softc *sc;

	sc = device_get_softc(dev);
	clock_unregister(sc->dev);
	bus_release_resource(sc->dev, SYS_RES_MEMORY, 0, sc->memres);
	return (0);
}