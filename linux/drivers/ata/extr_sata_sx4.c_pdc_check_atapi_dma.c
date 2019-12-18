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
typedef  int u8 ;
struct ata_queued_cmd {TYPE_1__* scsicmd; } ;
struct TYPE_2__ {int* cmnd; } ;

/* Variables and functions */
#define  READ_10 133 
#define  READ_12 132 
#define  READ_6 131 
#define  WRITE_10 130 
#define  WRITE_12 129 
#define  WRITE_6 128 

__attribute__((used)) static int pdc_check_atapi_dma(struct ata_queued_cmd *qc)
{
	u8 *scsicmd = qc->scsicmd->cmnd;
	int pio = 1; /* atapi dma off by default */

	/* Whitelist commands that may use DMA. */
	switch (scsicmd[0]) {
	case WRITE_12:
	case WRITE_10:
	case WRITE_6:
	case READ_12:
	case READ_10:
	case READ_6:
	case 0xad: /* READ_DVD_STRUCTURE */
	case 0xbe: /* READ_CD */
		pio = 0;
	}
	/* -45150 (FFFF4FA2) to -1 (FFFFFFFF) shall use PIO mode */
	if (scsicmd[0] == WRITE_10) {
		unsigned int lba =
			(scsicmd[2] << 24) |
			(scsicmd[3] << 16) |
			(scsicmd[4] << 8) |
			scsicmd[5];
		if (lba >= 0xFFFF4FA2)
			pio = 1;
	}
	return pio;
}