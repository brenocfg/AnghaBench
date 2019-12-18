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
struct aml8726_iic_softc {int /*<<< orphan*/ * iicbb; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 struct aml8726_iic_softc* device_get_softc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aml8726_iic_child_detached(device_t dev, device_t child)
{
	struct aml8726_iic_softc *sc = device_get_softc(dev);

	if (child == sc->iicbb)
		sc->iicbb = NULL;
}