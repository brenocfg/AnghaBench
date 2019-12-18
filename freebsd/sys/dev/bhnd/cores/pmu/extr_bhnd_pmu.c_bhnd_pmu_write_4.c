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
struct bhnd_pmu_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 void bhnd_bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhnd_pmu_write_4(bus_size_t reg, uint32_t val, void *ctx)
{
	struct bhnd_pmu_softc *sc = ctx;
	return (bhnd_bus_write_4(sc->res, reg, val));
}