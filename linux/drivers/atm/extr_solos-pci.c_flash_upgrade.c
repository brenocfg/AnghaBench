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
struct solos_card {scalar_t__ fpga_version; TYPE_1__* dev; scalar_t__ config_regs; int /*<<< orphan*/  fw_wq; scalar_t__ atmel_flash; } ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATMEL_FPGA_BLOCK ; 
 int ATMEL_SOLOS_BLOCK ; 
 scalar_t__ DRIVER_VER ; 
 int DRIVER_VERSION ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ FLASH_BLOCK ; 
 scalar_t__ FLASH_BUF ; 
 scalar_t__ FLASH_BUSY ; 
 scalar_t__ FLASH_MODE ; 
 scalar_t__ FPGA_MODE ; 
 scalar_t__ LEGACY_BUFFERS ; 
 scalar_t__ RX_BUF (struct solos_card*,int) ; 
 int SPI_FLASH_BLOCK ; 
 scalar_t__ WRITE_FLASH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int swahb32p (int*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int flash_upgrade(struct solos_card *card, int chip)
{
	const struct firmware *fw;
	const char *fw_name;
	int blocksize = 0;
	int numblocks = 0;
	int offset;

	switch (chip) {
	case 0:
		fw_name = "solos-FPGA.bin";
		if (card->atmel_flash)
			blocksize = ATMEL_FPGA_BLOCK;
		else
			blocksize = SPI_FLASH_BLOCK;
		break;
	case 1:
		fw_name = "solos-Firmware.bin";
		if (card->atmel_flash)
			blocksize = ATMEL_SOLOS_BLOCK;
		else
			blocksize = SPI_FLASH_BLOCK;
		break;
	case 2:
		if (card->fpga_version > LEGACY_BUFFERS){
			fw_name = "solos-db-FPGA.bin";
			if (card->atmel_flash)
				blocksize = ATMEL_FPGA_BLOCK;
			else
				blocksize = SPI_FLASH_BLOCK;
		} else {
			dev_info(&card->dev->dev, "FPGA version doesn't support"
					" daughter board upgrades\n");
			return -EPERM;
		}
		break;
	case 3:
		if (card->fpga_version > LEGACY_BUFFERS){
			fw_name = "solos-Firmware.bin";
			if (card->atmel_flash)
				blocksize = ATMEL_SOLOS_BLOCK;
			else
				blocksize = SPI_FLASH_BLOCK;
		} else {
			dev_info(&card->dev->dev, "FPGA version doesn't support"
					" daughter board upgrades\n");
			return -EPERM;
		}
		break;
	default:
		return -ENODEV;
	}

	if (request_firmware(&fw, fw_name, &card->dev->dev))
		return -ENOENT;

	dev_info(&card->dev->dev, "Flash upgrade starting\n");

	/* New FPGAs require driver version before permitting flash upgrades */
	iowrite32(DRIVER_VERSION, card->config_regs + DRIVER_VER);

	numblocks = fw->size / blocksize;
	dev_info(&card->dev->dev, "Firmware size: %zd\n", fw->size);
	dev_info(&card->dev->dev, "Number of blocks: %d\n", numblocks);
	
	dev_info(&card->dev->dev, "Changing FPGA to Update mode\n");
	iowrite32(1, card->config_regs + FPGA_MODE);
	(void) ioread32(card->config_regs + FPGA_MODE); 

	/* Set mode to Chip Erase */
	if(chip == 0 || chip == 2)
		dev_info(&card->dev->dev, "Set FPGA Flash mode to FPGA Chip Erase\n");
	if(chip == 1 || chip == 3)
		dev_info(&card->dev->dev, "Set FPGA Flash mode to Solos Chip Erase\n");
	iowrite32((chip * 2), card->config_regs + FLASH_MODE);


	iowrite32(1, card->config_regs + WRITE_FLASH);
	wait_event(card->fw_wq, !ioread32(card->config_regs + FLASH_BUSY));

	for (offset = 0; offset < fw->size; offset += blocksize) {
		int i;

		/* Clear write flag */
		iowrite32(0, card->config_regs + WRITE_FLASH);

		/* Set mode to Block Write */
		/* dev_info(&card->dev->dev, "Set FPGA Flash mode to Block Write\n"); */
		iowrite32(((chip * 2) + 1), card->config_regs + FLASH_MODE);

		/* Copy block to buffer, swapping each 16 bits for Atmel flash */
		for(i = 0; i < blocksize; i += 4) {
			uint32_t word;
			if (card->atmel_flash)
				word = swahb32p((uint32_t *)(fw->data + offset + i));
			else
				word = *(uint32_t *)(fw->data + offset + i);
			if(card->fpga_version > LEGACY_BUFFERS)
				iowrite32(word, FLASH_BUF + i);
			else
				iowrite32(word, RX_BUF(card, 3) + i);
		}

		/* Specify block number and then trigger flash write */
		iowrite32(offset / blocksize, card->config_regs + FLASH_BLOCK);
		iowrite32(1, card->config_regs + WRITE_FLASH);
		wait_event(card->fw_wq, !ioread32(card->config_regs + FLASH_BUSY));
	}

	release_firmware(fw);
	iowrite32(0, card->config_regs + WRITE_FLASH);
	iowrite32(0, card->config_regs + FPGA_MODE);
	iowrite32(0, card->config_regs + FLASH_MODE);
	dev_info(&card->dev->dev, "Returning FPGA to Data mode\n");
	return 0;
}