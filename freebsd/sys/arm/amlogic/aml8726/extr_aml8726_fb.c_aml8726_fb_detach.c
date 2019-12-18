#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_vbase; } ;
struct aml8726_fb_softc {TYPE_1__ info; int /*<<< orphan*/ * res; int /*<<< orphan*/  ih_cookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_FB_LOCK_DESTROY (struct aml8726_fb_softc*) ; 
 int /*<<< orphan*/  aml8726_fb_spec ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_fb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_fb_detach(device_t dev)
{
	struct aml8726_fb_softc *sc = device_get_softc(dev);

	bus_generic_detach(dev);

	bus_teardown_intr(dev, sc->res[3], sc->ih_cookie);

	AML_FB_LOCK_DESTROY(sc);

	bus_release_resources(dev, aml8726_fb_spec, sc->res);

	pmap_unmapdev(sc->info.fb_vbase, sc->info.fb_size);

	return (0);
}