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
typedef  int /*<<< orphan*/  uint32_t ;
struct aw_thermal_softc {TYPE_1__* conf; } ;
struct TYPE_2__ {int (* to_temp ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RD4 (struct aw_thermal_softc*,scalar_t__) ; 
 scalar_t__ THS_DATA0 ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aw_thermal_gettemp(struct aw_thermal_softc *sc, int sensor)
{
	uint32_t val;

	val = RD4(sc, THS_DATA0 + (sensor * 4));

	return (sc->conf->to_temp(val, sensor));
}