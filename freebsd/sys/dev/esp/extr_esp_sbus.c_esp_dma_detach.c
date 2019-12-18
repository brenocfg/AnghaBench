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
struct esp_softc {int /*<<< orphan*/  sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct esp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int espdetach (struct esp_softc*) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esp_dma_detach(device_t dev)
{
	struct esp_softc *esc;
	int error;

	esc = device_get_softc(dev);

	error = espdetach(esc);
	if (error != 0)
		return (error);
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(esc->sc_res),
	    esc->sc_res);

	return (0);
}