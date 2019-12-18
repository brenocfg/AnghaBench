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
struct aml8726_ccm_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CCM_LOCK_DESTROY (struct aml8726_ccm_softc*) ; 
 int /*<<< orphan*/  aml8726_ccm_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_ccm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_ccm_detach(device_t dev)
{
	struct aml8726_ccm_softc *sc = device_get_softc(dev);

	AML_CCM_LOCK_DESTROY(sc);

	bus_release_resources(dev, aml8726_ccm_spec, sc->res);

	return (0);
}