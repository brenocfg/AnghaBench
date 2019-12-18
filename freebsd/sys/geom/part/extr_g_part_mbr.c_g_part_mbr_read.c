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
typedef  void* u_int ;
typedef  void* u_char ;
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_table {scalar_t__ gpt_sectors; int gpt_entries; scalar_t__ gpt_first; scalar_t__ gpt_last; void* gpt_heads; int /*<<< orphan*/  gpt_fixgeom; } ;
struct g_part_mbr_table {int /*<<< orphan*/  mbr; } ;
struct dos_partition {scalar_t__ dp_typ; int dp_esect; scalar_t__ dp_start; scalar_t__ dp_size; void* dp_ecyl; void* dp_ehd; void* dp_scyl; void* dp_ssect; void* dp_shd; void* dp_flag; } ;
struct g_part_mbr_entry {struct dos_partition ent; } ;
struct g_consumer {struct g_provider* provider; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 scalar_t__ DOSPTYP_PMBR ; 
 scalar_t__ MIN (int,int /*<<< orphan*/ ) ; 
 int NDOSPART ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  bcopy (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_free (void**) ; 
 int /*<<< orphan*/  g_part_geometry_heads (scalar_t__,void*,scalar_t__*,void**) ; 
 scalar_t__ g_part_new_entry (struct g_part_table*,int,scalar_t__,scalar_t__) ; 
 void** g_read_data (struct g_consumer*,long,int,int*) ; 
 void* le32dec (void**) ; 

__attribute__((used)) static int
g_part_mbr_read(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct dos_partition ent;
	struct g_provider *pp;
	struct g_part_mbr_table *table;
	struct g_part_mbr_entry *entry;
	u_char *buf, *p;
	off_t chs, msize, first;
	u_int sectors, heads;
	int error, index;

	pp = cp->provider;
	table = (struct g_part_mbr_table *)basetable;
	first = basetable->gpt_sectors;
	msize = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX);

	buf = g_read_data(cp, 0L, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);

	bcopy(buf, table->mbr, sizeof(table->mbr));
	for (index = NDOSPART - 1; index >= 0; index--) {
		p = buf + DOSPARTOFF + index * DOSPARTSIZE;
		ent.dp_flag = p[0];
		ent.dp_shd = p[1];
		ent.dp_ssect = p[2];
		ent.dp_scyl = p[3];
		ent.dp_typ = p[4];
		ent.dp_ehd = p[5];
		ent.dp_esect = p[6];
		ent.dp_ecyl = p[7];
		ent.dp_start = le32dec(p + 8);
		ent.dp_size = le32dec(p + 12);
		if (ent.dp_typ == 0 || ent.dp_typ == DOSPTYP_PMBR)
			continue;
		if (ent.dp_start == 0 || ent.dp_size == 0)
			continue;
		sectors = ent.dp_esect & 0x3f;
		if (sectors > basetable->gpt_sectors &&
		    !basetable->gpt_fixgeom) {
			g_part_geometry_heads(msize, sectors, &chs, &heads);
			if (chs != 0) {
				basetable->gpt_sectors = sectors;
				basetable->gpt_heads = heads;
			}
		}
		if (ent.dp_start < first)
			first = ent.dp_start;
		entry = (struct g_part_mbr_entry *)g_part_new_entry(basetable,
		    index + 1, ent.dp_start, ent.dp_start + ent.dp_size - 1);
		entry->ent = ent;
	}

	basetable->gpt_entries = NDOSPART;
	basetable->gpt_first = basetable->gpt_sectors;
	basetable->gpt_last = msize - 1;

	if (first < basetable->gpt_first)
		basetable->gpt_first = 1;

	g_free(buf);
	return (0);
}