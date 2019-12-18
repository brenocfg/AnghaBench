#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {TYPE_1__* part; } ;
struct g_part_vtoc8_table {TYPE_2__ vtoc; } ;
struct g_part_table {int dummy; } ;
struct g_part_entry {int gpe_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 scalar_t__ VTOC_TAG_FREEBSD_SWAP ; 
 scalar_t__ VTOC_TAG_SWAP ; 
 scalar_t__ be16dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_vtoc8_dumpto(struct g_part_table *basetable,
    struct g_part_entry *entry)
{
	struct g_part_vtoc8_table *table;
	uint16_t tag;

	/*
	 * Allow dumping to a swap partition or a partition that
	 * has no type.
	 */
	table = (struct g_part_vtoc8_table *)basetable;
	tag = be16dec(&table->vtoc.part[entry->gpe_index - 1].tag);
	return ((tag == 0 || tag == VTOC_TAG_FREEBSD_SWAP ||
	    tag == VTOC_TAG_SWAP) ? 1 : 0);
}