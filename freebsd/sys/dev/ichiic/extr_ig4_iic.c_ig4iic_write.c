#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int txfifo_depth; } ;
struct TYPE_8__ {TYPE_1__ cfg; } ;
typedef  TYPE_2__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_DATA_RESTART ; 
 int /*<<< orphan*/  IG4_DATA_STOP ; 
 int IG4_FIFOLVL_MASK ; 
 int /*<<< orphan*/  IG4_FIFO_LOWAT ; 
 int /*<<< orphan*/  IG4_INTR_TX_EMPTY ; 
 int /*<<< orphan*/  IG4_REG_DATA_CMD ; 
 int /*<<< orphan*/  IG4_REG_TXFLR ; 
 int /*<<< orphan*/  IG4_REG_TX_TL ; 
 int MIN (int,int) ; 
 int reg_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_intr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ig4iic_write(ig4iic_softc_t *sc, uint8_t *buf, uint16_t len,
    bool repeated_start, bool stop)
{
	uint32_t cmd;
	int sent = 0;
	int burst, target;
	int error;
	bool lowat_set = false;

	if (len == 0)
		return (0);

	while (sent < len) {
		burst = sc->cfg.txfifo_depth -
		    (reg_read(sc, IG4_REG_TXFLR) & IG4_FIFOLVL_MASK);
		target = MIN(sent + burst, (int)len);
		/* Leave some data queued to maintain the hardware pipeline */
		if (!lowat_set && target != len) {
			lowat_set = true;
			reg_write(sc, IG4_REG_TX_TL, IG4_FIFO_LOWAT);
		}
		while(sent < target) {
			cmd = buf[sent];
			if (repeated_start && sent == 0)
				cmd |= IG4_DATA_RESTART;
			if (stop && sent == len - 1)
				cmd |= IG4_DATA_STOP;
			reg_write(sc, IG4_REG_DATA_CMD, cmd);
			sent++;
		}
		if (sent < len) {
			error = wait_intr(sc, IG4_INTR_TX_EMPTY);
			if (error)
				break;
		}
	}
	if (lowat_set)
		reg_write(sc, IG4_REG_TX_TL, 0);

	return (error);
}