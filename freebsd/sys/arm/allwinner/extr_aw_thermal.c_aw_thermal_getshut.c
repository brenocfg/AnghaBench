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
typedef  int uint32_t ;
struct aw_thermal_softc {TYPE_1__* conf; } ;
struct TYPE_2__ {int (* to_temp ) (int,int) ;} ;

/* Variables and functions */
 int RD4 (struct aw_thermal_softc*,scalar_t__) ; 
 int SHUT_T_HOT_MASK ; 
 int SHUT_T_HOT_SHIFT ; 
 scalar_t__ THS_SHUTDOWN0_CTRL ; 
 int stub1 (int,int) ; 

__attribute__((used)) static int
aw_thermal_getshut(struct aw_thermal_softc *sc, int sensor)
{
	uint32_t val;

	val = RD4(sc, THS_SHUTDOWN0_CTRL + (sensor * 4));
	val = (val >> SHUT_T_HOT_SHIFT) & SHUT_T_HOT_MASK;

	return (sc->conf->to_temp(val, sensor));
}