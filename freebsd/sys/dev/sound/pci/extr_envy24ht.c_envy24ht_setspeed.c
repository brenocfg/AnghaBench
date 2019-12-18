#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; TYPE_1__* cfg; } ;
struct TYPE_4__ {scalar_t__ speed; scalar_t__ code; } ;
struct TYPE_3__ {int scfg; } ;

/* Variables and functions */
 int ENVY24HT_CCSM_SCFG_XIN2 ; 
 int /*<<< orphan*/  ENVY24HT_MT_I2S ; 
 scalar_t__ ENVY24HT_MT_I2S_MLR128 ; 
 int /*<<< orphan*/  ENVY24HT_MT_RATE ; 
 scalar_t__ ENVY24HT_MT_RATE_176400 ; 
 scalar_t__ ENVY24HT_MT_RATE_192000 ; 
 scalar_t__ ENVY24HT_MT_RATE_MASK ; 
 scalar_t__ ENVY24HT_MT_RATE_SPDIF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ envy24ht_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24ht_slavecd (struct sc_info*) ; 
 TYPE_2__* envy24ht_speedtab ; 
 int /*<<< orphan*/  envy24ht_wrmt (struct sc_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static u_int32_t
envy24ht_setspeed(struct sc_info *sc, u_int32_t speed) {
	u_int32_t code, i2sfmt;
	int i = 0;

#if(0)
	device_printf(sc->dev, "envy24ht_setspeed(sc, %d)\n", speed);
	if (speed == 0) {
		code = ENVY24HT_MT_RATE_SPDIF; /* external master clock */
		envy24ht_slavecd(sc);
	}
	else {
#endif
		for (i = 0; envy24ht_speedtab[i].speed != 0; i++) {
			if (envy24ht_speedtab[i].speed == speed)
				break;
		}
		code = envy24ht_speedtab[i].code;
#if 0
	}
	device_printf(sc->dev, "envy24ht_setspeed(): speed %d/code 0x%04x\n", envy24ht_speedtab[i].speed, code);
#endif
	if (code < 0x10) {
		envy24ht_wrmt(sc, ENVY24HT_MT_RATE, code, 1);
		if ((((sc->cfg->scfg & ENVY24HT_CCSM_SCFG_XIN2) == 0x00) && (code == ENVY24HT_MT_RATE_192000)) || \
									    (code == ENVY24HT_MT_RATE_176400)) {
			i2sfmt = envy24ht_rdmt(sc, ENVY24HT_MT_I2S, 1);
			i2sfmt |= ENVY24HT_MT_I2S_MLR128;
			envy24ht_wrmt(sc, ENVY24HT_MT_I2S, i2sfmt, 1);
		}
		else {
			i2sfmt = envy24ht_rdmt(sc, ENVY24HT_MT_I2S, 1);
			i2sfmt &= ~ENVY24HT_MT_I2S_MLR128;
			envy24ht_wrmt(sc, ENVY24HT_MT_I2S, i2sfmt, 1);
		}
		code = envy24ht_rdmt(sc, ENVY24HT_MT_RATE, 1);
		code &= ENVY24HT_MT_RATE_MASK;
		for (i = 0; envy24ht_speedtab[i].code < 0x10; i++) {
			if (envy24ht_speedtab[i].code == code)
				break;
		}
		speed = envy24ht_speedtab[i].speed;
	}
	else
		speed = 0;

#if(0)
	device_printf(sc->dev, "envy24ht_setspeed(): return %d\n", speed);
#endif
	return speed;
}