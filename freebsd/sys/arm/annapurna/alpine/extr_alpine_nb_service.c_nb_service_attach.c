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
typedef  int /*<<< orphan*/  uint32_t ;
struct nb_service_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AL_NB_ACF_MISC_OFFSET ; 
 int /*<<< orphan*/  AL_NB_ACF_MISC_READ_BYPASS ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nb_service_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nb_service_spec ; 

__attribute__((used)) static int
nb_service_attach(device_t dev)
{
	struct nb_service_softc *sc;
	uint32_t val;
	int err;

	sc = device_get_softc(dev);

	err = bus_alloc_resources(dev, nb_service_spec, &sc->res);
	if (err != 0) {
		device_printf(dev, "could not allocate resources\n");
		return (err);
	}

	/* Do not allow reads to bypass writes to different addresses */
	val = bus_read_4(sc->res, AL_NB_ACF_MISC_OFFSET);
	val &= ~AL_NB_ACF_MISC_READ_BYPASS;
	bus_write_4(sc->res, AL_NB_ACF_MISC_OFFSET, val);

	return (0);
}