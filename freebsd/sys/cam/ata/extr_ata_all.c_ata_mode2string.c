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

/* Variables and functions */
 int ATA_DMA_MASK ; 
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

char *
ata_mode2string(int mode)
{
    switch (mode) {
    case -1: return "UNSUPPORTED";
    case 0: return "NONE";
    case ATA_PIO0: return "PIO0";
    case ATA_PIO1: return "PIO1";
    case ATA_PIO2: return "PIO2";
    case ATA_PIO3: return "PIO3";
    case ATA_PIO4: return "PIO4";
    case ATA_WDMA0: return "WDMA0";
    case ATA_WDMA1: return "WDMA1";
    case ATA_WDMA2: return "WDMA2";
    case ATA_UDMA0: return "UDMA0";
    case ATA_UDMA1: return "UDMA1";
    case ATA_UDMA2: return "UDMA2";
    case ATA_UDMA3: return "UDMA3";
    case ATA_UDMA4: return "UDMA4";
    case ATA_UDMA5: return "UDMA5";
    case ATA_UDMA6: return "UDMA6";
    default:
	if (mode & ATA_DMA_MASK)
	    return "BIOSDMA";
	else
	    return "BIOSPIO";
    }
}