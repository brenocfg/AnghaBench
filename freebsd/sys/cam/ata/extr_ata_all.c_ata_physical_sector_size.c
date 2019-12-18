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
typedef  int uint64_t ;
struct ata_params {int pss; } ;

/* Variables and functions */
 int ATA_PSS_LSPPS ; 
 int ATA_PSS_MULTLS ; 
 int ATA_PSS_VALID_MASK ; 
 int ATA_PSS_VALID_VALUE ; 
 scalar_t__ ata_logical_sector_size (struct ata_params*) ; 

uint64_t
ata_physical_sector_size(struct ata_params *ident_data)
{
	if ((ident_data->pss & ATA_PSS_VALID_MASK) == ATA_PSS_VALID_VALUE) {
		if (ident_data->pss & ATA_PSS_MULTLS) {
			return ((uint64_t)ata_logical_sector_size(ident_data) *
			    (1 << (ident_data->pss & ATA_PSS_LSPPS)));
		} else {
			return (uint64_t)ata_logical_sector_size(ident_data);
		}
	}
	return (512);
}