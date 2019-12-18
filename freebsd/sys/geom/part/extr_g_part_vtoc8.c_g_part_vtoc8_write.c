#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct g_provider {int /*<<< orphan*/  sectorsize; } ;
struct TYPE_6__ {int /*<<< orphan*/  cksum; TYPE_2__* map; TYPE_1__* part; } ;
struct g_part_vtoc8_table {TYPE_3__ vtoc; } ;
struct g_part_table {int gpt_entries; int /*<<< orphan*/  gpt_entry; } ;
struct g_part_entry {int gpe_index; scalar_t__ gpe_deleted; } ;
struct g_consumer {struct g_provider* provider; } ;
struct TYPE_5__ {int /*<<< orphan*/  nblks; int /*<<< orphan*/  cyl; } ;
struct TYPE_4__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 struct g_part_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_part_entry* LIST_NEXT (struct g_part_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int g_write_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpe_entry ; 

__attribute__((used)) static int
g_part_vtoc8_write(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_provider *pp;
	struct g_part_entry *entry;
	struct g_part_vtoc8_table *table;
	uint16_t sum;
	u_char *p;
	int error, index, match, offset;

	pp = cp->provider;
	table = (struct g_part_vtoc8_table *)basetable;
	entry = LIST_FIRST(&basetable->gpt_entry);
	for (index = 0; index < basetable->gpt_entries; index++) {
		match = (entry != NULL && index == entry->gpe_index - 1)
		    ? 1 : 0;
		if (match) {
			if (entry->gpe_deleted) {
				be16enc(&table->vtoc.part[index].tag, 0);
				be16enc(&table->vtoc.part[index].flag, 0);
				be32enc(&table->vtoc.map[index].cyl, 0);
				be32enc(&table->vtoc.map[index].nblks, 0);
			}
			entry = LIST_NEXT(entry, gpe_entry);
		}
	}

	/* Calculate checksum. */
	sum = 0;
	p = (void *)&table->vtoc;
	for (offset = 0; offset < sizeof(table->vtoc) - 2; offset += 2)
		sum ^= be16dec(p + offset);
	be16enc(&table->vtoc.cksum, sum);

	error = g_write_data(cp, 0, p, pp->sectorsize);
	return (error);
}