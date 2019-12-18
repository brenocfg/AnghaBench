#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_8__ {int /*<<< orphan*/  io_lock; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DO_POLL (TYPE_1__*) ; 
 int IG4_FIFOLVL_MASK ; 
 int IG4_INTR_ERR_MASK ; 
 int IG4_INTR_STOP_DET ; 
 int IG4_INTR_TX_EMPTY ; 
 int /*<<< orphan*/  IG4_REG_RAW_INTR_STAT ; 
 int /*<<< orphan*/  IG4_REG_TXFLR ; 
 int IIC_ETIMEOUT ; 
 int hz ; 
 int /*<<< orphan*/  ig4iic_set_intr_mask (TYPE_1__*,int) ; 
 int intrstat2iic (TYPE_1__*,int) ; 
 int /*<<< orphan*/  msleep_spin (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_intr(ig4iic_softc_t *sc, uint32_t intr)
{
	uint32_t v;
	int error;
	int txlvl = -1;
	u_int count_us = 0;
	u_int limit_us = 25000; /* 25ms */

	for (;;) {
		/*
		 * Check requested status
		 */
		v = reg_read(sc, IG4_REG_RAW_INTR_STAT);
		error = intrstat2iic(sc, v & IG4_INTR_ERR_MASK);
		if (error || (v & intr))
			break;

		/*
		 * When waiting for the transmit FIFO to become empty,
		 * reset the timeout if we see a change in the transmit
		 * FIFO level as progress is being made.
		 */
		if (intr & (IG4_INTR_TX_EMPTY | IG4_INTR_STOP_DET)) {
			v = reg_read(sc, IG4_REG_TXFLR) & IG4_FIFOLVL_MASK;
			if (txlvl != v) {
				txlvl = v;
				count_us = 0;
			}
		}

		/*
		 * Stop if we've run out of time.
		 */
		if (count_us >= limit_us) {
			error = IIC_ETIMEOUT;
			break;
		}

		/*
		 * When polling is not requested let the interrupt do its work.
		 */
		if (!DO_POLL(sc)) {
			mtx_lock_spin(&sc->io_lock);
			ig4iic_set_intr_mask(sc, intr | IG4_INTR_ERR_MASK);
			msleep_spin(sc, &sc->io_lock, "i2cwait",
				  (hz + 99) / 100); /* sleep up to 10ms */
			ig4iic_set_intr_mask(sc, 0);
			mtx_unlock_spin(&sc->io_lock);
			count_us += 10000;
		} else {
			DELAY(25);
			count_us += 25;
		}
	}

	return (error);
}