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
typedef  int u_char ;
struct g_provider {int sectorsize; int mediasize; } ;
struct g_part_table {scalar_t__ gpt_depth; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int DOSMAGIC ; 
 int DOSMAGICOFFSET ; 
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPT_HDR_SIG ; 
 int G_PART_PROBE_PRI_HIGH ; 
 int G_PART_PROBE_PRI_LOW ; 
 int MBRSIZE ; 
 int NDOSPART ; 
 int /*<<< orphan*/  allow_nesting ; 
 int /*<<< orphan*/  g_free (int*) ; 
 int* g_read_data (struct g_consumer*,long,int,int*) ; 
 int le16dec (int*) ; 
 int memcmp (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
g_part_gpt_probe(struct g_part_table *table, struct g_consumer *cp)
{
	struct g_provider *pp;
	u_char *buf;
	int error, index, pri, res;

	/* Our depth should be 0 unless nesting was explicitly enabled. */
	if (!allow_nesting && table->gpt_depth != 0)
		return (ENXIO);

	pp = cp->provider;

	/*
	 * Sanity-check the provider. Since the first sector on the provider
	 * must be a PMBR and a PMBR is 512 bytes large, the sector size
	 * must be at least 512 bytes.  Also, since the theoretical minimum
	 * number of sectors needed by GPT is 6, any medium that has less
	 * than 6 sectors is never going to be able to hold a GPT. The
	 * number 6 comes from:
	 *	1 sector for the PMBR
	 *	2 sectors for the GPT headers (each 1 sector)
	 *	2 sectors for the GPT tables (each 1 sector)
	 *	1 sector for an actual partition
	 * It's better to catch this pathological case early than behaving
	 * pathologically later on...
	 */
	if (pp->sectorsize < MBRSIZE || pp->mediasize < 6 * pp->sectorsize)
		return (ENOSPC);

	/*
	 * Check that there's a MBR or a PMBR. If it's a PMBR, we return
	 * as the highest priority on a match, otherwise we assume some
	 * GPT-unaware tool has destroyed the GPT by recreating a MBR and
	 * we really want the MBR scheme to take precedence.
	 */
	buf = g_read_data(cp, 0L, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);
	res = le16dec(buf + DOSMAGICOFFSET);
	pri = G_PART_PROBE_PRI_LOW;
	if (res == DOSMAGIC) {
		for (index = 0; index < NDOSPART; index++) {
			if (buf[DOSPARTOFF + DOSPARTSIZE * index + 4] == 0xee)
				pri = G_PART_PROBE_PRI_HIGH;
		}
		g_free(buf);

		/* Check that there's a primary header. */
		buf = g_read_data(cp, pp->sectorsize, pp->sectorsize, &error);
		if (buf == NULL)
			return (error);
		res = memcmp(buf, GPT_HDR_SIG, 8);
		g_free(buf);
		if (res == 0)
			return (pri);
	} else
		g_free(buf);

	/* No primary? Check that there's a secondary. */
	buf = g_read_data(cp, pp->mediasize - pp->sectorsize, pp->sectorsize,
	    &error);
	if (buf == NULL)
		return (error);
	res = memcmp(buf, GPT_HDR_SIG, 8);
	g_free(buf);
	return ((res == 0) ? pri : ENXIO);
}