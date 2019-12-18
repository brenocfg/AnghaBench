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
struct s10_svc_softc {int /*<<< orphan*/ * callfn; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct s10_svc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ s10_get_memory (struct s10_svc_softc*) ; 
 int /*<<< orphan*/ * s10_svc_get_callfn (struct s10_svc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
s10_svc_attach(device_t dev)
{
	struct s10_svc_softc *sc;
	phandle_t node;

	node = ofw_bus_get_node(dev);

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (device_get_unit(dev) != 0)
		return (ENXIO);

	sc->callfn = s10_svc_get_callfn(sc, node);
	if (sc->callfn == NULL)
		return (ENXIO);

	if (s10_get_memory(sc) != 0)
		return (ENXIO);

	return (0);
}