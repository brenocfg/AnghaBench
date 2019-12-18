#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct g_provider {int sectorsize; int mediasize; char* name; } ;
struct TYPE_8__ {TYPE_3__* part; TYPE_1__* map; int /*<<< orphan*/  nparts; int /*<<< orphan*/  sanity; TYPE_3__* volume; int /*<<< orphan*/  version; int /*<<< orphan*/  ncyls; int /*<<< orphan*/  nheads; int /*<<< orphan*/  nsecs; } ;
struct g_part_vtoc8_table {int secpercyl; TYPE_4__ vtoc; } ;
struct g_part_table {int gpt_sectors; int gpt_heads; int gpt_last; int gpt_isleaf; int gpt_entries; scalar_t__ gpt_first; int /*<<< orphan*/  gpt_fixgeom; } ;
struct g_part_entry {int gpe_internal; } ;
struct g_consumer {struct g_provider* provider; } ;
typedef  int off_t ;
struct TYPE_7__ {int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int gps_minent; int gps_maxent; } ;
struct TYPE_5__ {int /*<<< orphan*/  nblks; int /*<<< orphan*/  cyl; } ;

/* Variables and functions */
 int EINVAL ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 scalar_t__ VTOC8_NPARTS ; 
 int VTOC_RAW_PART ; 
 int VTOC_SANITY ; 
 scalar_t__ VTOC_TAG_BACKUP ; 
 scalar_t__ VTOC_TAG_UNASSIGNED ; 
 int VTOC_VERSION ; 
 int VTOC_VOLUME_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 void* be16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,scalar_t__) ; 
 int be32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (TYPE_3__**,int) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_part_geometry_heads (int,int,int*,int*) ; 
 struct g_part_entry* g_part_new_entry (struct g_part_table*,int,int,int) ; 
 TYPE_2__ g_part_vtoc8_scheme ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static int
g_part_vtoc8_read(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_provider *pp;
	struct g_part_vtoc8_table *table;
	struct g_part_entry *entry;
	u_char *buf;
	off_t chs, msize;
	uint64_t offset, size;
	u_int cyls, heads, sectors;
	int error, index, withtags;
	uint16_t tag;

	pp = cp->provider;
	buf = g_read_data(cp, 0, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);

	table = (struct g_part_vtoc8_table *)basetable;
	bcopy(buf, &table->vtoc, sizeof(table->vtoc));
	g_free(buf);

	msize = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX);
	sectors = be16dec(&table->vtoc.nsecs);
	if (sectors < 1)
		goto invalid_label;
	if (sectors != basetable->gpt_sectors && !basetable->gpt_fixgeom) {
		g_part_geometry_heads(msize, sectors, &chs, &heads);
		if (chs != 0) {
			basetable->gpt_sectors = sectors;
			basetable->gpt_heads = heads;
		}
	}

	heads = be16dec(&table->vtoc.nheads);
	if (heads < 1)
		goto invalid_label;
	if (heads != basetable->gpt_heads && !basetable->gpt_fixgeom)
		basetable->gpt_heads = heads;
	/*
	 * Except for ATA disks > 32GB, Solaris uses the native geometry
	 * as reported by the target for the labels while da(4) typically
	 * uses a synthetic one so we don't complain too loudly if these
	 * geometries don't match.
	 */
	if (bootverbose && (sectors != basetable->gpt_sectors ||
	    heads != basetable->gpt_heads))
		printf("GEOM: %s: geometry does not match VTOC8 label "
		    "(label: %uh,%us GEOM: %uh,%us).\n", pp->name, heads,
		    sectors, basetable->gpt_heads, basetable->gpt_sectors);

	table->secpercyl = heads * sectors;
	cyls = be16dec(&table->vtoc.ncyls);
	chs = cyls * table->secpercyl;
	if (chs < 1 || chs > msize)
		goto invalid_label;

	basetable->gpt_first = 0;
	basetable->gpt_last = chs - 1;
	basetable->gpt_isleaf = 1;

	withtags = (be32dec(&table->vtoc.sanity) == VTOC_SANITY) ? 1 : 0;
	if (!withtags) {
		printf("GEOM: %s: adding VTOC8 information.\n", pp->name);
		be32enc(&table->vtoc.version, VTOC_VERSION);
		bzero(&table->vtoc.volume, VTOC_VOLUME_LEN);
		be16enc(&table->vtoc.nparts, VTOC8_NPARTS);
		bzero(&table->vtoc.part, sizeof(table->vtoc.part));
		be32enc(&table->vtoc.sanity, VTOC_SANITY);
	}

	basetable->gpt_entries = be16dec(&table->vtoc.nparts);
	if (basetable->gpt_entries < g_part_vtoc8_scheme.gps_minent ||
	    basetable->gpt_entries > g_part_vtoc8_scheme.gps_maxent)
		goto invalid_label;

	for (index = basetable->gpt_entries - 1; index >= 0; index--) {
		offset = be32dec(&table->vtoc.map[index].cyl) *
		    table->secpercyl;
		size = be32dec(&table->vtoc.map[index].nblks);
		if (size == 0)
			continue;
		if (withtags)
			tag = be16dec(&table->vtoc.part[index].tag);
		else
			tag = (index == VTOC_RAW_PART)
			    ? VTOC_TAG_BACKUP
			    : VTOC_TAG_UNASSIGNED;

		if (index == VTOC_RAW_PART && tag != VTOC_TAG_BACKUP)
			continue;
		if (index != VTOC_RAW_PART && tag == VTOC_TAG_BACKUP)
			continue;
		entry = g_part_new_entry(basetable, index + 1, offset,
		    offset + size - 1);
		if (tag == VTOC_TAG_BACKUP)
			entry->gpe_internal = 1;

		if (!withtags)
			be16enc(&table->vtoc.part[index].tag, tag);
	}

	return (0);

 invalid_label:
	printf("GEOM: %s: invalid VTOC8 label.\n", pp->name);
	return (EINVAL);
}