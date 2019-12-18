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
typedef  int uint32_t ;
struct aw_ir_softc {int /*<<< orphan*/  dev; scalar_t__ dcnt; int /*<<< orphan*/  sc_evdev; } ;

/* Variables and functions */
 int AW_IR_RXINT_RAI_EN ; 
 int AW_IR_RXINT_ROI_EN ; 
 int AW_IR_RXINT_RPEI_EN ; 
 int /*<<< orphan*/  AW_IR_RXSTA ; 
 int AW_IR_RXSTA_CLEARALL ; 
 int AW_IR_RXSTA_COUNTER (int) ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int READ (struct aw_ir_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE (struct aw_ir_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ aw_ir_buf_full (struct aw_ir_softc*) ; 
 int /*<<< orphan*/  aw_ir_buf_reset (struct aw_ir_softc*) ; 
 int /*<<< orphan*/  aw_ir_buf_write (struct aw_ir_softc*,int /*<<< orphan*/ ) ; 
 unsigned long aw_ir_decode_packets (struct aw_ir_softc*) ; 
 int /*<<< orphan*/  aw_ir_read_data (struct aw_ir_softc*) ; 
 int aw_ir_validate_code (unsigned long) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  evdev_push_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  evdev_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aw_ir_intr(void *arg)
{
	struct aw_ir_softc *sc;
	uint32_t val;
	int i, dcnt;
	unsigned long ir_code;
	int stat;

	sc = (struct aw_ir_softc *)arg;

	/* Read RX interrupt status */
	val = READ(sc, AW_IR_RXSTA);
	if (bootverbose)
		device_printf(sc->dev, "RX interrupt status: %x\n", val);

	/* Clean all pending interrupt statuses */
	WRITE(sc, AW_IR_RXSTA, val | AW_IR_RXSTA_CLEARALL);

	/* When Rx FIFO Data available or Packet end */
	if (val & (AW_IR_RXINT_RAI_EN | AW_IR_RXINT_RPEI_EN)) {
		if (bootverbose)
			device_printf(sc->dev,
			    "RX FIFO Data available or Packet end\n");
		/* Get available message count in RX FIFO */
		dcnt  = AW_IR_RXSTA_COUNTER(val);
		/* Read FIFO */
		for (i = 0; i < dcnt; i++) {
			if (aw_ir_buf_full(sc)) {
				if (bootverbose)
					device_printf(sc->dev,
					    "raw buffer full\n");
				break;
			} else
				aw_ir_buf_write(sc, aw_ir_read_data(sc));
		}
	}

	if (val & AW_IR_RXINT_RPEI_EN) {
		/* RX Packet end */
		if (bootverbose)
			device_printf(sc->dev, "RX Packet end\n");
		ir_code = aw_ir_decode_packets(sc);
		stat = aw_ir_validate_code(ir_code);
		if (stat == 0) {
			evdev_push_event(sc->sc_evdev,
			    EV_MSC, MSC_SCAN, ir_code);
			evdev_sync(sc->sc_evdev);
		}
		if (bootverbose) {
			device_printf(sc->dev, "Final IR code: %lx\n",
			    ir_code);
			device_printf(sc->dev, "IR code status: %d\n",
			    stat);
		}
		sc->dcnt = 0;
	}
	if (val & AW_IR_RXINT_ROI_EN) {
		/* RX FIFO overflow */
		if (bootverbose)
			device_printf(sc->dev, "RX FIFO overflow\n");
		/* Flush raw buffer */
		aw_ir_buf_reset(sc);
	}
}