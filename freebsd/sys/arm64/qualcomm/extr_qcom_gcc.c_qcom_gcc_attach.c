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
struct qcom_gcc_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qcom_gcc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qcom_gcc_spec ; 
 int /*<<< orphan*/  qcom_qdss_enable (struct qcom_gcc_softc*) ; 

__attribute__((used)) static int
qcom_gcc_attach(device_t dev)
{
	struct qcom_gcc_softc *sc;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, qcom_gcc_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	/*
	 * Enable debug unit.
	 * This is required for Coresight operation.
	 * This also enables USB clock branch.
	 */
	qcom_qdss_enable(sc);

	return (0);
}