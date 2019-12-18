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
struct g_part_table {scalar_t__ gpt_entries; scalar_t__ gpt_last; scalar_t__ gpt_first; } ;
struct TYPE_4__ {int ent_pmblkcnt; scalar_t__ ent_size; } ;
struct TYPE_3__ {scalar_t__ ddr_blkcount; } ;
struct g_part_apm_table {int /*<<< orphan*/  tivo_series1; TYPE_2__ self; TYPE_1__ ddr; } ;
struct apm_ent {scalar_t__ ent_size; scalar_t__ ent_start; int /*<<< orphan*/  ent_type; } ;
struct g_part_apm_entry {struct apm_ent ent; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_ENT_TYPE_UNUSED ; 
 int apm_read_ent (struct g_consumer*,int,struct apm_ent*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_part_new_entry (struct g_part_table*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_apm_read(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct apm_ent ent;
	struct g_part_apm_entry *entry;
	struct g_part_apm_table *table;
	int error, index;

	table = (struct g_part_apm_table *)basetable;

	basetable->gpt_first = table->self.ent_size + 1;
	basetable->gpt_last = table->ddr.ddr_blkcount - 1;
	basetable->gpt_entries = table->self.ent_size - 1;

	for (index = table->self.ent_pmblkcnt - 1; index > 0; index--) {
		error = apm_read_ent(cp, index + 1, &ent, table->tivo_series1);
		if (error)
			continue;
		if (!strcmp(ent.ent_type, APM_ENT_TYPE_UNUSED))
			continue;
		entry = (struct g_part_apm_entry *)g_part_new_entry(basetable,
		    index, ent.ent_start, ent.ent_start + ent.ent_size - 1);
		entry->ent = ent;
	}

	return (0);
}