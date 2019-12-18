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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct vtoc8 {int dummy; } ;
struct g_provider {int sectorsize; int mediasize; } ;
struct TYPE_6__ {TYPE_2__* map; TYPE_1__* part; int /*<<< orphan*/  magic; int /*<<< orphan*/  nsecs; int /*<<< orphan*/  nheads; int /*<<< orphan*/  altcyls; int /*<<< orphan*/  ncyls; int /*<<< orphan*/  physcyls; int /*<<< orphan*/  rpm; int /*<<< orphan*/  sanity; int /*<<< orphan*/  nparts; int /*<<< orphan*/  version; int /*<<< orphan*/  ascii; } ;
struct g_part_vtoc8_table {int secpercyl; TYPE_3__ vtoc; } ;
struct g_part_table {int gpt_sectors; int gpt_heads; int gpt_last; int gpt_isleaf; scalar_t__ gpt_first; } ;
struct g_part_parms {struct g_provider* gpp_provider; } ;
struct g_part_entry {int gpe_internal; } ;
struct TYPE_5__ {int /*<<< orphan*/  nblks; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int ENOSPC ; 
 int ENXIO ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int VTOC8_NPARTS ; 
 int VTOC_MAGIC ; 
 int VTOC_RAW_PART ; 
 int VTOC_SANITY ; 
 int VTOC_TAG_BACKUP ; 
 int VTOC_VERSION ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int) ; 
 struct g_part_entry* g_part_new_entry (struct g_part_table*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,long long,int,int,int,int) ; 

__attribute__((used)) static int
g_part_vtoc8_create(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_provider *pp;
	struct g_part_entry *entry;
	struct g_part_vtoc8_table *table;
	uint64_t msize;
	uint32_t acyls, ncyls, pcyls;

	pp = gpp->gpp_provider;

	if (pp->sectorsize < sizeof(struct vtoc8))
		return (ENOSPC);
	if (pp->sectorsize > sizeof(struct vtoc8))
		return (ENXIO);

	table = (struct g_part_vtoc8_table *)basetable;

	msize = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX);
	table->secpercyl = basetable->gpt_sectors * basetable->gpt_heads;
	pcyls = msize / table->secpercyl;
	acyls = 2;
	ncyls = pcyls - acyls;
	msize = ncyls * table->secpercyl;

	sprintf(table->vtoc.ascii, "FreeBSD%lldM cyl %u alt %u hd %u sec %u",
	    (long long)(msize / 2048), ncyls, acyls, basetable->gpt_heads,
	    basetable->gpt_sectors);
	be32enc(&table->vtoc.version, VTOC_VERSION);
	be16enc(&table->vtoc.nparts, VTOC8_NPARTS);
	be32enc(&table->vtoc.sanity, VTOC_SANITY);
	be16enc(&table->vtoc.rpm, 3600);
	be16enc(&table->vtoc.physcyls, pcyls);
	be16enc(&table->vtoc.ncyls, ncyls);
	be16enc(&table->vtoc.altcyls, acyls);
	be16enc(&table->vtoc.nheads, basetable->gpt_heads);
	be16enc(&table->vtoc.nsecs, basetable->gpt_sectors);
	be16enc(&table->vtoc.magic, VTOC_MAGIC);

	basetable->gpt_first = 0;
	basetable->gpt_last = msize - 1;
	basetable->gpt_isleaf = 1;

	entry = g_part_new_entry(basetable, VTOC_RAW_PART + 1,
	    basetable->gpt_first, basetable->gpt_last);
	entry->gpe_internal = 1;
	be16enc(&table->vtoc.part[VTOC_RAW_PART].tag, VTOC_TAG_BACKUP);
	be32enc(&table->vtoc.map[VTOC_RAW_PART].nblks, msize);
	return (0);
}