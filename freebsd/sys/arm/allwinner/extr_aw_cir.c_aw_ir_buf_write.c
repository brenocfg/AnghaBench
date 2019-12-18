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
struct aw_ir_softc {scalar_t__ dcnt; unsigned char* buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AW_IR_RAW_BUF_SIZE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
aw_ir_buf_write(struct aw_ir_softc *sc, unsigned char data)
{

	if (sc->dcnt < AW_IR_RAW_BUF_SIZE)
		sc->buf[sc->dcnt++] = data;
	else
		if (bootverbose)
			device_printf(sc->dev, "IR RX Buffer Full!\n");
}