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
struct ata_params {int lsalign; } ;

/* Variables and functions */
 scalar_t__ ata_logical_sector_size (struct ata_params*) ; 

uint64_t
ata_logical_sector_offset(struct ata_params *ident_data)
{
	if ((ident_data->lsalign & 0xc000) == 0x4000) {
		return ((uint64_t)ata_logical_sector_size(ident_data) *
		    (ident_data->lsalign & 0x3fff));
	}
	return (0);
}