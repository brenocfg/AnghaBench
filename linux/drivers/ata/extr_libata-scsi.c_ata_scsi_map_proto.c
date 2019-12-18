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
typedef  int u8 ;

/* Variables and functions */
 int ATA_PROT_DMA ; 
 int ATA_PROT_NCQ ; 
 int ATA_PROT_NODATA ; 
 int ATA_PROT_PIO ; 
 int ATA_PROT_UNKNOWN ; 

__attribute__((used)) static u8
ata_scsi_map_proto(u8 byte1)
{
	switch((byte1 & 0x1e) >> 1) {
	case 3:		/* Non-data */
		return ATA_PROT_NODATA;

	case 6:		/* DMA */
	case 10:	/* UDMA Data-in */
	case 11:	/* UDMA Data-Out */
		return ATA_PROT_DMA;

	case 4:		/* PIO Data-in */
	case 5:		/* PIO Data-out */
		return ATA_PROT_PIO;

	case 12:	/* FPDMA */
		return ATA_PROT_NCQ;

	case 0:		/* Hard Reset */
	case 1:		/* SRST */
	case 8:		/* Device Diagnostic */
	case 9:		/* Device Reset */
	case 7:		/* DMA Queued */
	case 15:	/* Return Response Info */
	default:	/* Reserved */
		break;
	}

	return ATA_PROT_UNKNOWN;
}