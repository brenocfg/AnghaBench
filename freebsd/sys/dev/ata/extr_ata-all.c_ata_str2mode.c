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
 int ATA_PIO0 ; 
 int ATA_PIO1 ; 
 int ATA_PIO2 ; 
 int ATA_PIO3 ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int ATA_UDMA1 ; 
 int ATA_UDMA2 ; 
 int ATA_UDMA3 ; 
 int ATA_UDMA4 ; 
 int ATA_UDMA5 ; 
 int ATA_UDMA6 ; 
 int ATA_WDMA0 ; 
 int ATA_WDMA1 ; 
 int ATA_WDMA2 ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
ata_str2mode(const char *str)
{

	if (!strcasecmp(str, "PIO0")) return (ATA_PIO0);
	if (!strcasecmp(str, "PIO1")) return (ATA_PIO1);
	if (!strcasecmp(str, "PIO2")) return (ATA_PIO2);
	if (!strcasecmp(str, "PIO3")) return (ATA_PIO3);
	if (!strcasecmp(str, "PIO4")) return (ATA_PIO4);
	if (!strcasecmp(str, "WDMA0")) return (ATA_WDMA0);
	if (!strcasecmp(str, "WDMA1")) return (ATA_WDMA1);
	if (!strcasecmp(str, "WDMA2")) return (ATA_WDMA2);
	if (!strcasecmp(str, "UDMA0")) return (ATA_UDMA0);
	if (!strcasecmp(str, "UDMA16")) return (ATA_UDMA0);
	if (!strcasecmp(str, "UDMA1")) return (ATA_UDMA1);
	if (!strcasecmp(str, "UDMA25")) return (ATA_UDMA1);
	if (!strcasecmp(str, "UDMA2")) return (ATA_UDMA2);
	if (!strcasecmp(str, "UDMA33")) return (ATA_UDMA2);
	if (!strcasecmp(str, "UDMA3")) return (ATA_UDMA3);
	if (!strcasecmp(str, "UDMA44")) return (ATA_UDMA3);
	if (!strcasecmp(str, "UDMA4")) return (ATA_UDMA4);
	if (!strcasecmp(str, "UDMA66")) return (ATA_UDMA4);
	if (!strcasecmp(str, "UDMA5")) return (ATA_UDMA5);
	if (!strcasecmp(str, "UDMA100")) return (ATA_UDMA5);
	if (!strcasecmp(str, "UDMA6")) return (ATA_UDMA6);
	if (!strcasecmp(str, "UDMA133")) return (ATA_UDMA6);
	return (-1);
}