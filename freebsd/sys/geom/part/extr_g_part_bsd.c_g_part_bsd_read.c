#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  void* u_char ;
struct partition {int p_size; int p_offset; void* p_cpg; void* p_frag; void* p_fstype; void* p_fsize; } ;
struct g_provider {int mediasize; int sectorsize; char* name; } ;
struct g_part_table {int gpt_sectors; int gpt_heads; int gpt_last; int gpt_isleaf; int gpt_entries; scalar_t__ gpt_first; int /*<<< orphan*/  gpt_fixgeom; } ;
struct g_part_entry {int gpe_internal; } ;
struct g_part_bsd_table {void** bbarea; int offset; } ;
struct g_part_bsd_entry {struct partition part; } ;
struct g_consumer {struct g_provider* provider; } ;
typedef  int off_t ;
struct TYPE_2__ {int gps_minent; int gps_maxent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBSIZE ; 
 int EINVAL ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int RAW_PART ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  g_free (void**) ; 
 TYPE_1__ g_part_bsd_scheme ; 
 int /*<<< orphan*/  g_part_geometry_heads (int,int,int*,int*) ; 
 struct g_part_entry* g_part_new_entry (struct g_part_table*,int,int,int) ; 
 void** g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* le16dec (void**) ; 
 void* le32dec (void**) ; 
 int /*<<< orphan*/  le32enc (void**,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
g_part_bsd_read(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_provider *pp;
	struct g_part_bsd_table *table;
	struct g_part_entry *baseentry;
	struct g_part_bsd_entry *entry;
	struct partition part;
	u_char *buf, *p;
	off_t chs, msize;
	u_int sectors, heads;
	int error, index;

	pp = cp->provider;
	table = (struct g_part_bsd_table *)basetable;
	msize = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX);

	table->bbarea = g_read_data(cp, 0, BBSIZE, &error);
	if (table->bbarea == NULL)
		return (error);

	buf = table->bbarea + pp->sectorsize;

	if (le32dec(buf + 40) != pp->sectorsize)
		goto invalid_label;
	sectors = le32dec(buf + 44);
	if (sectors < 1 || sectors > 255)
		goto invalid_label;
	if (sectors != basetable->gpt_sectors && !basetable->gpt_fixgeom) {
		g_part_geometry_heads(msize, sectors, &chs, &heads);
		if (chs != 0) {
			basetable->gpt_sectors = sectors;
			basetable->gpt_heads = heads;
		}
	}
	heads = le32dec(buf + 48);
	if (heads < 1 || heads > 255)
		goto invalid_label;
	if (heads != basetable->gpt_heads && !basetable->gpt_fixgeom)
		basetable->gpt_heads = heads;

	chs = le32dec(buf + 60);
	if (chs < 1)
		goto invalid_label;
	/* Fix-up a sysinstall bug. */
	if (chs > msize) {
		chs = msize;
		le32enc(buf + 60, msize);
	}

	basetable->gpt_first = 0;
	basetable->gpt_last = msize - 1;
	basetable->gpt_isleaf = 1;

	basetable->gpt_entries = le16dec(buf + 138);
	if (basetable->gpt_entries < g_part_bsd_scheme.gps_minent ||
	    basetable->gpt_entries > g_part_bsd_scheme.gps_maxent)
		goto invalid_label;

	table->offset = le32dec(buf + 148 + RAW_PART * 16 + 4);
	for (index = basetable->gpt_entries - 1; index >= 0; index--) {
		p = buf + 148 + index * 16;
		part.p_size = le32dec(p + 0);
		part.p_offset = le32dec(p + 4);
		part.p_fsize = le32dec(p + 8);
		part.p_fstype = p[12];
		part.p_frag = p[13];
		part.p_cpg = le16dec(p + 14);
		if (part.p_size == 0)
			continue;
		if (part.p_offset < table->offset)
			continue;
		if (part.p_offset - table->offset > basetable->gpt_last)
			goto invalid_label;
		baseentry = g_part_new_entry(basetable, index + 1,
		    part.p_offset - table->offset,
		    part.p_offset - table->offset + part.p_size - 1);
		entry = (struct g_part_bsd_entry *)baseentry;
		entry->part = part;
		if (index == RAW_PART)
			baseentry->gpe_internal = 1;
	}

	return (0);

 invalid_label:
	printf("GEOM: %s: invalid disklabel.\n", pp->name);
	g_free(table->bbarea);
	table->bbarea = NULL;
	return (EINVAL);
}