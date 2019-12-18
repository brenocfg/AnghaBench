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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  CF_16 130 
#define  CF_8 129 
#define  CF_TRUE_IDE_8 128 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int STATUS_BSY ; 
 int /*<<< orphan*/  TF_COMMAND ; 
 int /*<<< orphan*/  TF_CYL_LSB ; 
 int /*<<< orphan*/  TF_CYL_MSB ; 
 int /*<<< orphan*/  TF_DRV_HEAD ; 
 int /*<<< orphan*/  TF_SECTOR_COUNT ; 
 int /*<<< orphan*/  TF_SECTOR_NUMBER ; 
 int /*<<< orphan*/  TF_STATUS ; 
 int /*<<< orphan*/  WAIT_DELAY ; 
 int bus_type ; 
 int cf_inb_16 (int /*<<< orphan*/ ) ; 
 int cf_inb_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_outb_8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cf_outw_16 (int /*<<< orphan*/ ,int) ; 
 int cf_wait_busy () ; 

__attribute__((used)) static int cf_send_cmd (uint32_t lba, uint8_t cmd)
{
	switch (bus_type)
	{
	case CF_8:
	case CF_TRUE_IDE_8:
		while (cf_inb_8(TF_STATUS) & STATUS_BSY)
			DELAY(WAIT_DELAY);
		cf_outb_8(TF_SECTOR_COUNT, 1);
		cf_outb_8(TF_SECTOR_NUMBER, lba & 0xff);
		cf_outb_8(TF_CYL_LSB, (lba >> 8) & 0xff);
		cf_outb_8(TF_CYL_MSB, (lba >> 16) & 0xff);
		cf_outb_8(TF_DRV_HEAD, ((lba >> 24) & 0xff) | 0xe0);
		cf_outb_8(TF_COMMAND, cmd);
		break;
	case CF_16:
	default:
		while (cf_inb_16(TF_STATUS) & STATUS_BSY)
			DELAY(WAIT_DELAY);
		cf_outw_16(TF_SECTOR_COUNT, 1 | ((lba & 0xff) << 8));
		cf_outw_16(TF_CYL_LSB, ((lba >> 8) & 0xff) | (((lba >> 16) & 0xff) << 8));
		cf_outw_16(TF_DRV_HEAD, (((lba >> 24) & 0xff) | 0xe0) | (cmd << 8));
		break;
	}

	return (cf_wait_busy());
}