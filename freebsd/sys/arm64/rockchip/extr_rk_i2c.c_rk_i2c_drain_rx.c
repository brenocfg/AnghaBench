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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rk_i2c_softc {int cnt; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int len; int* buf; } ;

/* Variables and functions */
 int RK_I2C_READ (struct rk_i2c_softc*,scalar_t__) ; 
 scalar_t__ RK_I2C_RXDATA_BASE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
rk_i2c_drain_rx(struct rk_i2c_softc *sc)
{
	uint32_t buf32 = 0;
	uint8_t buf8;
	int len;
	int i;

	if (sc->msg == NULL) {
		device_printf(sc->dev, "No current iic msg\n");
		return;
	}

	len = sc->msg->len - sc->cnt;
	if (len > 32)
		len = 32;

	for (i = 0; i < len; i++) {
		if (i % 4 == 0)
			buf32 = RK_I2C_READ(sc, RK_I2C_RXDATA_BASE + (i / 4) * 4);

		buf8 = (buf32 >> ((i % 4) * 8)) & 0xFF;
		sc->msg->buf[sc->cnt++] = buf8;
	}
}