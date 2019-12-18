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
struct smuiic_softc {int /*<<< orphan*/  sc_busno; scalar_t__ sc_iic_inuse; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct smuiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smuiic_attach(device_t dev)
{
	struct smuiic_softc *sc = device_get_softc(dev);
	mtx_init(&sc->sc_mtx, "smuiic", NULL, MTX_DEF);
	sc->sc_iic_inuse = 0;

	/* Get our bus number */
	OF_getprop(ofw_bus_get_node(dev), "reg", &sc->sc_busno,
	    sizeof(sc->sc_busno));

	/* Add the IIC bus layer */
	device_add_child(dev, "iicbus", -1);

	return (bus_generic_attach(dev));
}