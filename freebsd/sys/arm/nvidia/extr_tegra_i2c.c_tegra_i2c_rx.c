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
struct tegra_i2c_softc {size_t msg_idx; TYPE_1__* msg; } ;
struct TYPE_2__ {size_t len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FIFO_STATUS ; 
 scalar_t__ I2C_FIFO_STATUS_RX_FIFO_FULL_CNT (int) ; 
 int /*<<< orphan*/  I2C_RX_FIFO ; 
 int RD4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ) ; 
 int min (int,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
tegra_i2c_rx(struct tegra_i2c_softc *sc)
{
	uint32_t reg;
	int cnt, i;

	if (sc->msg_idx >= sc->msg->len)
		panic("Invalid call to tegra_i2c_rx\n");

	while(sc->msg_idx < sc->msg->len) {
		reg = RD4(sc, I2C_FIFO_STATUS);
		if (I2C_FIFO_STATUS_RX_FIFO_FULL_CNT(reg) == 0)
			break;
		cnt = min(4, sc->msg->len - sc->msg_idx);
		reg = RD4(sc, I2C_RX_FIFO);
		for (i = 0;  i < cnt; i++) {
			sc->msg->buf[sc->msg_idx] = (reg >> (i * 8)) & 0xFF;
			sc->msg_idx++;
		}
	}

	if (sc->msg_idx >= sc->msg->len)
		return (0);
	return (sc->msg->len - sc->msg_idx - 1);
}