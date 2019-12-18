#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 scalar_t__ E6000SW_WAITREADY (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int VTU_BUSY ; 
 int VTU_FLUSH ; 
 int /*<<< orphan*/  VTU_OPERATION ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e6000sw_writereg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e6000sw_vtu_flush(e6000sw_softc_t *sc)
{

	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "VTU unit is busy, cannot access\n");
		return (EBUSY);
	}

	e6000sw_writereg(sc, REG_GLOBAL, VTU_OPERATION, VTU_FLUSH | VTU_BUSY);
	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "Timeout while flushing VTU\n");
		return (ETIMEDOUT);
	}

	return (0);
}