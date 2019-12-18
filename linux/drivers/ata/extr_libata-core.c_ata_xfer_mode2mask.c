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
typedef  scalar_t__ u8 ;
struct ata_xfer_ent {int shift; scalar_t__ base; scalar_t__ bits; } ;

/* Variables and functions */
 struct ata_xfer_ent* ata_xfer_tbl ; 

unsigned long ata_xfer_mode2mask(u8 xfer_mode)
{
	const struct ata_xfer_ent *ent;

	for (ent = ata_xfer_tbl; ent->shift >= 0; ent++)
		if (xfer_mode >= ent->base && xfer_mode < ent->base + ent->bits)
			return ((2 << (ent->shift + xfer_mode - ent->base)) - 1)
				& ~((1 << ent->shift) - 1);
	return 0;
}