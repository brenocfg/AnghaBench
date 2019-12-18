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
struct ata_ering_entry {scalar_t__ err_mask; } ;
struct ata_ering {size_t cursor; struct ata_ering_entry* ring; } ;

/* Variables and functions */

__attribute__((used)) static struct ata_ering_entry *ata_ering_top(struct ata_ering *ering)
{
	struct ata_ering_entry *ent = &ering->ring[ering->cursor];

	if (ent->err_mask)
		return ent;
	return NULL;
}