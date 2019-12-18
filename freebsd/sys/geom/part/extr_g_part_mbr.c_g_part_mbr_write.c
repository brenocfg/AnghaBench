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
typedef  int /*<<< orphan*/  u_char ;
struct g_part_table {int gpt_entries; int /*<<< orphan*/  gpt_entry; } ;
struct g_part_mbr_table {int /*<<< orphan*/ * mbr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dp_size; int /*<<< orphan*/  dp_start; int /*<<< orphan*/  dp_ecyl; int /*<<< orphan*/  dp_esect; int /*<<< orphan*/  dp_ehd; int /*<<< orphan*/  dp_typ; int /*<<< orphan*/  dp_scyl; int /*<<< orphan*/  dp_ssect; int /*<<< orphan*/  dp_shd; int /*<<< orphan*/  dp_flag; } ;
struct g_part_mbr_entry {TYPE_1__ ent; } ;
struct g_part_entry {int gpe_index; int /*<<< orphan*/  gpe_deleted; } ;
struct g_consumer {TYPE_2__* provider; } ;
struct TYPE_4__ {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 struct g_part_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_part_entry* LIST_NEXT (struct g_part_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int g_write_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpe_entry ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_mbr_write(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_part_entry *baseentry;
	struct g_part_mbr_entry *entry;
	struct g_part_mbr_table *table;
	u_char *p;
	int error, index;

	table = (struct g_part_mbr_table *)basetable;
	baseentry = LIST_FIRST(&basetable->gpt_entry);
	for (index = 1; index <= basetable->gpt_entries; index++) {
		p = table->mbr + DOSPARTOFF + (index - 1) * DOSPARTSIZE;
		entry = (baseentry != NULL && index == baseentry->gpe_index)
		    ? (struct g_part_mbr_entry *)baseentry : NULL;
		if (entry != NULL && !baseentry->gpe_deleted) {
			p[0] = entry->ent.dp_flag;
			p[1] = entry->ent.dp_shd;
			p[2] = entry->ent.dp_ssect;
			p[3] = entry->ent.dp_scyl;
			p[4] = entry->ent.dp_typ;
			p[5] = entry->ent.dp_ehd;
			p[6] = entry->ent.dp_esect;
			p[7] = entry->ent.dp_ecyl;
			le32enc(p + 8, entry->ent.dp_start);
			le32enc(p + 12, entry->ent.dp_size);
		} else
			bzero(p, DOSPARTSIZE);

		if (entry != NULL)
			baseentry = LIST_NEXT(baseentry, gpe_entry);
	}

	error = g_write_data(cp, 0, table->mbr, cp->provider->sectorsize);
	return (error);
}