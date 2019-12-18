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
struct lsi64854_softc {int /*<<< orphan*/  sc_res; int /*<<< orphan*/  sc_parent_dmat; } ;
struct esp_softc {int /*<<< orphan*/  sc_res; struct lsi64854_softc* sc_dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct esp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int espdetach (struct esp_softc*) ; 
 int /*<<< orphan*/  free (struct lsi64854_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
esp_sbus_detach(device_t dev)
{
	struct esp_softc *esc;
	struct lsi64854_softc *lsc;
	int error;

	esc = device_get_softc(dev);
	lsc = esc->sc_dma;

	error = espdetach(esc);
	if (error != 0)
		return (error);
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(esc->sc_res),
		esc->sc_res);
	if (strcmp(ofw_bus_get_name(dev), "SUNW,fas") != 0)
		return (0);
	bus_dma_tag_destroy(lsc->sc_parent_dmat);
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(lsc->sc_res),
	    lsc->sc_res);
	free(lsc, M_DEVBUF);

	return (0);
}