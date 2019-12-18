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
typedef  int const u64 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ ata_id_current_chs_valid (int const*) ; 
 scalar_t__ ata_id_has_lba (int const*) ; 
 scalar_t__ ata_id_has_lba48 (int const*) ; 
 int const ata_id_u32 (int const*,int) ; 
 int const ata_id_u64 (int const*,int) ; 

__attribute__((used)) static u64 ata_id_n_sectors(const u16 *id)
{
	if (ata_id_has_lba(id)) {
		if (ata_id_has_lba48(id))
			return ata_id_u64(id, 100);
		else
			return ata_id_u32(id, 60);
	} else {
		if (ata_id_current_chs_valid(id))
			return ata_id_u32(id, 57);
		else
			return id[1] * id[3] * id[6];
	}
}