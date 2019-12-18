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
typedef  scalar_t__ u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ speed; scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_MT_RATE ; 
 scalar_t__ ENVY24_MT_RATE_MASK ; 
 scalar_t__ ENVY24_MT_RATE_SPDIF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_slavecd (struct sc_info*) ; 
 TYPE_1__* envy24_speedtab ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static u_int32_t
envy24_setspeed(struct sc_info *sc, u_int32_t speed) {
	u_int32_t code;
	int i = 0;

#if(0)
	device_printf(sc->dev, "envy24_setspeed(sc, %d)\n", speed);
#endif
	if (speed == 0) {
		code = ENVY24_MT_RATE_SPDIF; /* external master clock */
		envy24_slavecd(sc);
	}
	else {
		for (i = 0; envy24_speedtab[i].speed != 0; i++) {
			if (envy24_speedtab[i].speed == speed)
				break;
		}
		code = envy24_speedtab[i].code;
	}
#if(0)
	device_printf(sc->dev, "envy24_setspeed(): speed %d/code 0x%04x\n", envy24_speedtab[i].speed, code);
#endif
	if (code < 0x10) {
		envy24_wrmt(sc, ENVY24_MT_RATE, code, 1);
		code = envy24_rdmt(sc, ENVY24_MT_RATE, 1);
		code &= ENVY24_MT_RATE_MASK;
		for (i = 0; envy24_speedtab[i].code < 0x10; i++) {
			if (envy24_speedtab[i].code == code)
				break;
		}
		speed = envy24_speedtab[i].speed;
	}
	else
		speed = 0;

#if(0)
	device_printf(sc->dev, "envy24_setspeed(): return %d\n", speed);
#endif
	return speed;
}