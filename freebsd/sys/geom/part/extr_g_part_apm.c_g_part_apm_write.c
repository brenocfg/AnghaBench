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
typedef  size_t uint32_t ;
struct g_provider {size_t sectorsize; } ;
struct g_part_table {int /*<<< orphan*/  gpt_entry; scalar_t__ gpt_created; } ;
struct g_part_entry {size_t gpe_index; int /*<<< orphan*/  gpe_deleted; } ;
struct TYPE_5__ {size_t ent_pmblkcnt; size_t ent_start; size_t ent_size; int /*<<< orphan*/  ent_type; int /*<<< orphan*/  ent_name; } ;
struct TYPE_4__ {size_t ddr_blkcount; int /*<<< orphan*/  ddr_blksize; int /*<<< orphan*/  ddr_sig; } ;
struct g_part_apm_table {TYPE_2__ self; TYPE_1__ ddr; scalar_t__ tivo_series1; } ;
struct TYPE_6__ {size_t ent_start; size_t ent_size; int /*<<< orphan*/  ent_type; int /*<<< orphan*/  ent_name; } ;
struct g_part_apm_entry {TYPE_3__ ent; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_ENT_SIG ; 
 int /*<<< orphan*/  APM_ENT_TYPE_UNUSED ; 
 int EOPNOTSUPP ; 
 struct g_part_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_part_entry* LIST_NEXT (struct g_part_entry*,int /*<<< orphan*/ ) ; 
 size_t MAXPHYS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  be16enc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (char*,size_t) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_malloc (size_t,int) ; 
 int g_write_data (struct g_consumer*,int,char*,size_t) ; 
 int /*<<< orphan*/  gpe_entry ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_apm_write(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_provider *pp;
	struct g_part_entry *baseentry;
	struct g_part_apm_entry *entry;
	struct g_part_apm_table *table;
	char *buf, *ptr;
	uint32_t index;
	int error;
	size_t tblsz;

	pp = cp->provider;
	table = (struct g_part_apm_table *)basetable;
	/*
	 * Tivo Series 1 disk partitions are currently read-only.
	 */
	if (table->tivo_series1)
		return (EOPNOTSUPP);

	/* Write the DDR only when we're newly created. */
	if (basetable->gpt_created) {
		buf = g_malloc(pp->sectorsize, M_WAITOK | M_ZERO);
		be16enc(buf, table->ddr.ddr_sig);
		be16enc(buf + 2, table->ddr.ddr_blksize);
		be32enc(buf + 4, table->ddr.ddr_blkcount);
		error = g_write_data(cp, 0, buf, pp->sectorsize);
		g_free(buf);
		if (error)
			return (error);
	}

	/* Allocate the buffer for all entries */
	tblsz = table->self.ent_pmblkcnt;
	buf = g_malloc(tblsz * pp->sectorsize, M_WAITOK | M_ZERO);

	/* Fill the self entry */
	be16enc(buf, APM_ENT_SIG);
	be32enc(buf + 4, table->self.ent_pmblkcnt);
	be32enc(buf + 8, table->self.ent_start);
	be32enc(buf + 12, table->self.ent_size);
	bcopy(table->self.ent_name, buf + 16, sizeof(table->self.ent_name));
	bcopy(table->self.ent_type, buf + 48, sizeof(table->self.ent_type));

	baseentry = LIST_FIRST(&basetable->gpt_entry);
	for (index = 1; index < tblsz; index++) {
		entry = (baseentry != NULL && index == baseentry->gpe_index)
		    ? (struct g_part_apm_entry *)baseentry : NULL;
		ptr = buf + index * pp->sectorsize;
		be16enc(ptr, APM_ENT_SIG);
		be32enc(ptr + 4, table->self.ent_pmblkcnt);
		if (entry != NULL && !baseentry->gpe_deleted) {
			be32enc(ptr + 8, entry->ent.ent_start);
			be32enc(ptr + 12, entry->ent.ent_size);
			bcopy(entry->ent.ent_name, ptr + 16,
			    sizeof(entry->ent.ent_name));
			bcopy(entry->ent.ent_type, ptr + 48,
			    sizeof(entry->ent.ent_type));
		} else {
			strcpy(ptr + 48, APM_ENT_TYPE_UNUSED);
		}
		if (entry != NULL)
			baseentry = LIST_NEXT(baseentry, gpe_entry);
	}

	for (index = 0; index < tblsz; index += MAXPHYS / pp->sectorsize) {
		error = g_write_data(cp, (1 + index) * pp->sectorsize,
		    buf + index * pp->sectorsize,
		    (tblsz - index > MAXPHYS / pp->sectorsize) ? MAXPHYS:
		    (tblsz - index) * pp->sectorsize);
		if (error) {
			g_free(buf);
			return (error);
		}
	}
	g_free(buf);
	return (0);
}