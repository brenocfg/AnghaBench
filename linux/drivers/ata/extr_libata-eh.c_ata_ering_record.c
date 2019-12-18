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
struct ata_ering_entry {unsigned int eflags; unsigned int err_mask; int /*<<< orphan*/  timestamp; } ;
struct ata_ering {size_t cursor; struct ata_ering_entry* ring; } ;

/* Variables and functions */
 size_t ATA_ERING_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 

__attribute__((used)) static void ata_ering_record(struct ata_ering *ering, unsigned int eflags,
			     unsigned int err_mask)
{
	struct ata_ering_entry *ent;

	WARN_ON(!err_mask);

	ering->cursor++;
	ering->cursor %= ATA_ERING_SIZE;

	ent = &ering->ring[ering->cursor];
	ent->eflags = eflags;
	ent->err_mask = err_mask;
	ent->timestamp = get_jiffies_64();
}