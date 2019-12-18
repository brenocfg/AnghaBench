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
typedef  int /*<<< orphan*/  uint16_t ;
struct tsensor {char* name; scalar_t__ sensor_base; scalar_t__ therm_b; scalar_t__ therm_a; TYPE_1__* cfg; } ;
struct soctherm_softc {int dummy; } ;
struct soctherm_shared_cal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ten_count; int /*<<< orphan*/  tiddq_en; scalar_t__ tsample; int /*<<< orphan*/  tall; } ;

/* Variables and functions */
 int RD4 (struct soctherm_softc*,scalar_t__) ; 
 scalar_t__ TSENSOR_CONFIG0 ; 
 int TSENSOR_CONFIG0_STATUS_CLR ; 
 int TSENSOR_CONFIG0_STOP ; 
 int TSENSOR_CONFIG0_TALL (int /*<<< orphan*/ ) ; 
 scalar_t__ TSENSOR_CONFIG1 ; 
 int TSENSOR_CONFIG1_TEMP_ENABLE ; 
 int TSENSOR_CONFIG1_TEN_COUNT (int /*<<< orphan*/ ) ; 
 int TSENSOR_CONFIG1_TIDDQ_EN (int /*<<< orphan*/ ) ; 
 int TSENSOR_CONFIG1_TSAMPLE (scalar_t__) ; 
 scalar_t__ TSENSOR_CONFIG2 ; 
 int TSENSOR_CONFIG2_THERMA (int /*<<< orphan*/ ) ; 
 int TSENSOR_CONFIG2_THERMB (int /*<<< orphan*/ ) ; 
 scalar_t__ TSENSOR_STATUS0 ; 
 scalar_t__ TSENSOR_STATUS1 ; 
 scalar_t__ TSENSOR_STATUS2 ; 
 int /*<<< orphan*/  WR4 (struct soctherm_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  tsensor_calibration (struct tsensor*,struct soctherm_shared_cal*) ; 

__attribute__((used)) static void
soctherm_init_tsensor(struct soctherm_softc *sc, struct tsensor *sensor,
    struct soctherm_shared_cal *shared_cal)
{
	uint32_t val;

	tsensor_calibration(sensor, shared_cal);

	val = RD4(sc, sensor->sensor_base + TSENSOR_CONFIG0);
	val |= TSENSOR_CONFIG0_STOP;
	val |= TSENSOR_CONFIG0_STATUS_CLR;
	WR4(sc, sensor->sensor_base + TSENSOR_CONFIG0, val);

	val = TSENSOR_CONFIG0_TALL(sensor->cfg->tall);
	val |= TSENSOR_CONFIG0_STOP;
	WR4(sc, sensor->sensor_base + TSENSOR_CONFIG0, val);

	val = TSENSOR_CONFIG1_TSAMPLE(sensor->cfg->tsample - 1);
	val |= TSENSOR_CONFIG1_TIDDQ_EN(sensor->cfg->tiddq_en);
	val |= TSENSOR_CONFIG1_TEN_COUNT(sensor->cfg->ten_count);
	val |= TSENSOR_CONFIG1_TEMP_ENABLE;
	WR4(sc, sensor->sensor_base + TSENSOR_CONFIG1, val);

	val = TSENSOR_CONFIG2_THERMA((uint16_t)sensor->therm_a) |
	     TSENSOR_CONFIG2_THERMB((uint16_t)sensor->therm_b);
	WR4(sc, sensor->sensor_base + TSENSOR_CONFIG2, val);

	val = RD4(sc, sensor->sensor_base + TSENSOR_CONFIG0);
	val &= ~TSENSOR_CONFIG0_STOP;
	WR4(sc, sensor->sensor_base + TSENSOR_CONFIG0, val);
#ifdef DEBUG
	printf(" Sensor: %s  cfg:0x%08X, 0x%08X, 0x%08X,"
	    " sts:0x%08X, 0x%08X, 0x%08X\n", sensor->name,
	    RD4(sc, sensor->sensor_base + TSENSOR_CONFIG0),
	    RD4(sc, sensor->sensor_base + TSENSOR_CONFIG1),
	    RD4(sc, sensor->sensor_base + TSENSOR_CONFIG2),
	    RD4(sc, sensor->sensor_base + TSENSOR_STATUS0),
	    RD4(sc, sensor->sensor_base + TSENSOR_STATUS1),
	    RD4(sc, sensor->sensor_base + TSENSOR_STATUS2)
	    );
#endif
}