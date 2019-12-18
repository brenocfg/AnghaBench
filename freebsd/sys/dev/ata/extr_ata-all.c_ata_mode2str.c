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
#define  ATA_PIO0 145 
#define  ATA_PIO1 144 
#define  ATA_PIO2 143 
#define  ATA_PIO3 142 
#define  ATA_PIO4 141 
#define  ATA_SA150 140 
#define  ATA_SA300 139 
#define  ATA_SA600 138 
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

const char *
ata_mode2str(int mode)
{
    switch (mode) {
    case -1: return "UNSUPPORTED";
    case ATA_PIO0: return "PIO0";
    case ATA_PIO1: return "PIO1";
    case ATA_PIO2: return "PIO2";
    case ATA_PIO3: return "PIO3";
    case ATA_PIO4: return "PIO4";
    case ATA_WDMA0: return "WDMA0";
    case ATA_WDMA1: return "WDMA1";
    case ATA_WDMA2: return "WDMA2";
    case ATA_UDMA0: return "UDMA16";
    case ATA_UDMA1: return "UDMA25";
    case ATA_UDMA2: return "UDMA33";
    case ATA_UDMA3: return "UDMA40";
    case ATA_UDMA4: return "UDMA66";
    case ATA_UDMA5: return "UDMA100";
    case ATA_UDMA6: return "UDMA133";
    case ATA_SA150: return "SATA150";
    case ATA_SA300: return "SATA300";
    case ATA_SA600: return "SATA600";
    default:
	if (mode & ATA_DMA_MASK)
	    return "BIOSDMA";
	else
	    return "BIOSPIO";
    }
}