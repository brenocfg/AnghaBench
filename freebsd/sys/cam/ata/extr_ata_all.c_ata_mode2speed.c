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

/* Variables and functions */
#define  ATA_PIO0 142 
#define  ATA_PIO1 141 
#define  ATA_PIO2 140 
#define  ATA_PIO3 139 
#define  ATA_PIO4 138 
#define  ATA_UDMA0 137 
#define  ATA_UDMA1 136 
#define  ATA_UDMA2 135 
#define  ATA_UDMA3 134 
#define  ATA_UDMA4 133 
#define  ATA_UDMA5 132 
#define  ATA_UDMA6 131 
#define  ATA_WDMA0 130 
#define  ATA_WDMA1 129 
#define  ATA_WDMA2 128 

u_int
ata_mode2speed(int mode)
{
	switch (mode) {
	case ATA_PIO0:
	default:
		return (3300);
	case ATA_PIO1:
		return (5200);
	case ATA_PIO2:
		return (8300);
	case ATA_PIO3:
		return (11100);
	case ATA_PIO4:
		return (16700);
	case ATA_WDMA0:
		return (4200);
	case ATA_WDMA1:
		return (13300);
	case ATA_WDMA2:
		return (16700);
	case ATA_UDMA0:
		return (16700);
	case ATA_UDMA1:
		return (25000);
	case ATA_UDMA2:
		return (33300);
	case ATA_UDMA3:
		return (44400);
	case ATA_UDMA4:
		return (66700);
	case ATA_UDMA5:
		return (100000);
	case ATA_UDMA6:
		return (133000);
	}
}