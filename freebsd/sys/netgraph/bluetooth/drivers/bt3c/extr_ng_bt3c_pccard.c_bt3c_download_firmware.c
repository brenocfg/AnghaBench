#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_9__ {int block_address; int block_size; scalar_t__ block_alignment; } ;
typedef  TYPE_1__ ng_bt3c_firmware_block_ep ;
typedef  TYPE_2__* bt3c_softc_p ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bt3c_read_control (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bt3c_set_address (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bt3c_write (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  bt3c_write_control (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bt3c_write_data (TYPE_2__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
bt3c_download_firmware(bt3c_softc_p sc, char const *firmware, int firmware_size)
{
	ng_bt3c_firmware_block_ep const	*block = NULL;
	u_int16_t const			*data = NULL;
	int				 i, size;
	u_int8_t			 c;

	/* Reset */
	device_printf(sc->dev, "Reseting the card...\n");
	bt3c_write(sc, 0x8040, 0x0404);
	bt3c_write(sc, 0x8040, 0x0400);
	DELAY(1);

	bt3c_write(sc, 0x8040, 0x0404);
	DELAY(17);

	/* Download firmware */
	device_printf(sc->dev, "Starting firmware download process...\n");

	for (size = 0; size < firmware_size; ) {
		block = (ng_bt3c_firmware_block_ep const *)(firmware + size);
		data = (u_int16_t const *)(block + 1);

		if (bootverbose)
			device_printf(sc->dev, "Download firmware block, " \
				"address=%#08x, size=%d words, aligment=%d\n",
				block->block_address, block->block_size,
				block->block_alignment);

		bt3c_set_address(sc, block->block_address);
		for (i = 0; i < block->block_size; i++)
			bt3c_write_data(sc, data[i]);

		size += (sizeof(*block) + (block->block_size * 2) + 
				block->block_alignment);
	}

	DELAY(17);
	device_printf(sc->dev, "Firmware download process complete\n");

	/* Boot */
	device_printf(sc->dev, "Starting the card...\n");
	bt3c_set_address(sc, 0x3000);
	bt3c_read_control(sc, c);
	bt3c_write_control(sc, (c | 0x40));
	DELAY(17);

	/* Clear registers */
	device_printf(sc->dev, "Clearing card registers...\n");
	bt3c_write(sc, 0x7006, 0x0000);
	bt3c_write(sc, 0x7005, 0x0000);
	bt3c_write(sc, 0x7001, 0x0000);
	DELAY(1000);
}