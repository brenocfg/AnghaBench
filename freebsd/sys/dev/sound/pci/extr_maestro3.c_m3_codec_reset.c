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
typedef  int u_int16_t ;
struct sc_info {int delay1; int delay2; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int COMMAND_ADDR_OUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GPIO_DATA ; 
 int /*<<< orphan*/  GPIO_DIRECTION ; 
 int /*<<< orphan*/  GPIO_MASK ; 
 int GPO_PRIMARY_AC97 ; 
 int IO_SRAM_ENABLE ; 
 int /*<<< orphan*/  M3_LOCK_ASSERT (struct sc_info*) ; 
 int /*<<< orphan*/  RING_BUS_CTRL_A ; 
 int /*<<< orphan*/  RING_BUS_CTRL_B ; 
 int /*<<< orphan*/  SDO_IN_DEST_CTRL ; 
 int /*<<< orphan*/  SDO_OUT_DEST_CTRL ; 
 int SECOND_CODEC_ID_MASK ; 
 int SERIAL_AC_LINK_ENABLE ; 
 int STATUS_ADDR_IN ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int m3_rd_2 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int m3_rdcd (int /*<<< orphan*/ *,struct sc_info*,int) ; 
 int /*<<< orphan*/  m3_wr_2 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
m3_codec_reset(struct sc_info *sc)
{
	u_int16_t data, dir;
	int retry = 0;

	M3_LOCK_ASSERT(sc);
	do {
		data = m3_rd_2(sc, GPIO_DIRECTION);
		dir = data | 0x10; /* assuming pci bus master? */

		/* [[remote_codec_config]] */
		data = m3_rd_2(sc, RING_BUS_CTRL_B);
		m3_wr_2(sc, RING_BUS_CTRL_B, data & ~SECOND_CODEC_ID_MASK);
		data = m3_rd_2(sc, SDO_OUT_DEST_CTRL);
		m3_wr_2(sc, SDO_OUT_DEST_CTRL, data & ~COMMAND_ADDR_OUT);
		data = m3_rd_2(sc, SDO_IN_DEST_CTRL);
		m3_wr_2(sc, SDO_IN_DEST_CTRL, data & ~STATUS_ADDR_IN);

		m3_wr_2(sc, RING_BUS_CTRL_A, IO_SRAM_ENABLE);
		DELAY(20);

		m3_wr_2(sc, GPIO_DIRECTION, dir & ~GPO_PRIMARY_AC97);
		m3_wr_2(sc, GPIO_MASK, ~GPO_PRIMARY_AC97);
		m3_wr_2(sc, GPIO_DATA, 0);
		m3_wr_2(sc, GPIO_DIRECTION, dir | GPO_PRIMARY_AC97);
		DELAY(sc->delay1 * 1000); /*delay1 (ALLEGRO:50, MAESTRO3:20)*/
		m3_wr_2(sc, GPIO_DATA, GPO_PRIMARY_AC97);
		DELAY(5);
		m3_wr_2(sc, RING_BUS_CTRL_A, IO_SRAM_ENABLE |
		    SERIAL_AC_LINK_ENABLE);
		m3_wr_2(sc, GPIO_MASK, ~0);
		DELAY(sc->delay2 * 1000); /*delay2 (ALLEGRO:800, MAESTRO3:500)*/

		/* [[try read vendor]] */
		data = m3_rdcd(NULL, sc, 0x7c);
		if ((data == 0) || (data == 0xffff)) {
			retry++;
			if (retry > 3) {
				device_printf(sc->dev, "Codec reset failed\n");
				break;
			}
			device_printf(sc->dev, "Codec reset retry\n");
		} else retry = 0;
	} while (retry);
}