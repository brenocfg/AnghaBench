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
#define  ATAPI_PROT_DMA 135 
#define  ATAPI_PROT_NODATA 134 
#define  ATAPI_PROT_PIO 133 
#define  ATA_PROT_DMA 132 
#define  ATA_PROT_NCQ 131 
#define  ATA_PROT_NCQ_NODATA 130 
#define  ATA_PROT_NODATA 129 
#define  ATA_PROT_PIO 128 

__attribute__((used)) static const char *get_prot_descript(u8 protocol)
{
	switch (protocol) {
	case ATA_PROT_NODATA:
		return "ATA no data";
	case ATA_PROT_PIO:
		return "ATA PIO";
	case ATA_PROT_DMA:
		return "ATA DMA";
	case ATA_PROT_NCQ:
		return "ATA NCQ";
	case ATA_PROT_NCQ_NODATA:
		return "ATA NCQ no data";
	case ATAPI_PROT_NODATA:
		return "ATAPI no data";
	case ATAPI_PROT_PIO:
		return "ATAPI PIO";
	case ATAPI_PROT_DMA:
		return "ATAPI DMA";
	default:
		return "unknown";
	}
}