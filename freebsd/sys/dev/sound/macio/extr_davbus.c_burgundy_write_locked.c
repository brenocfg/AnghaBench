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
typedef  int u_int ;
struct davbus_softc {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int BURGUNDY_CTRL_RESET ; 
 int BURGUNDY_CTRL_WRITE ; 
 int DAVBUS_CODEC_BUSY ; 
 int /*<<< orphan*/  DAVBUS_CODEC_CTRL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
burgundy_write_locked(struct davbus_softc *d, u_int reg, u_int val)
{
	u_int size, addr, offset, data, i;

	size = (reg & 0x00FF0000) >> 16;
	addr = (reg & 0x0000FF00) >> 8;
	offset = reg & 0xFF;

	for (i = offset; i < offset + size; ++i) {
		data = BURGUNDY_CTRL_WRITE | (addr << 12) | 
		    ((size + offset - 1) << 10) | (i << 8) | (val & 0xFF);
		if (i == offset)
			data |= BURGUNDY_CTRL_RESET;

		bus_write_4(d->reg, DAVBUS_CODEC_CTRL, data);

		while (bus_read_4(d->reg, DAVBUS_CODEC_CTRL) &
		    DAVBUS_CODEC_BUSY)
			DELAY(1);
		
		val >>= 8; /* next byte. */
	}	
}