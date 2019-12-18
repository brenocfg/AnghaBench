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
typedef  scalar_t__ uint16_t ;
typedef  int u_char ;
struct g_provider {int sectorsize; int mediasize; } ;
struct g_part_table {int dummy; } ;
struct g_consumer {struct g_provider* provider; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DOSMAGIC ; 
 int DOSMAGICOFFSET ; 
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 int ELOOP ; 
 int ENOSPC ; 
 int ENXIO ; 
 int G_PART_PROBE_PRI_NORM ; 
 int MBRSIZE ; 
 int NDOSPART ; 
 int /*<<< orphan*/  g_free (int*) ; 
 int g_getattr (char*,struct g_consumer*,char**) ; 
 TYPE_1__ g_part_mbr_scheme ; 
 int* g_read_data (struct g_consumer*,long,int,int*) ; 
 scalar_t__ le16dec (int*) ; 
 int /*<<< orphan*/  mbr_probe_bpb (int*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_mbr_probe(struct g_part_table *table, struct g_consumer *cp)
{
	char psn[8];
	struct g_provider *pp;
	u_char *buf, *p;
	int error, index, res, sum;
	uint16_t magic;

	pp = cp->provider;

	/* Sanity-check the provider. */
	if (pp->sectorsize < MBRSIZE || pp->mediasize < pp->sectorsize)
		return (ENOSPC);
	if (pp->sectorsize > 4096)
		return (ENXIO);

	/* We don't nest under an MBR (see EBR instead). */
	error = g_getattr("PART::scheme", cp, &psn);
	if (error == 0 && strcmp(psn, g_part_mbr_scheme.name) == 0)
		return (ELOOP);

	/* Check that there's a MBR. */
	buf = g_read_data(cp, 0L, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);

	/* We goto out on mismatch. */
	res = ENXIO;

	magic = le16dec(buf + DOSMAGICOFFSET);
	if (magic != DOSMAGIC)
		goto out;

	for (index = 0; index < NDOSPART; index++) {
		p = buf + DOSPARTOFF + index * DOSPARTSIZE;
		if (p[0] != 0 && p[0] != 0x80)
			goto out;
	}

	/*
	 * If the partition table does not consist of all zeroes,
	 * assume we have a MBR. If it's all zeroes, we could have
	 * a boot sector. For example, a boot sector that doesn't
	 * have boot code -- common on non-i386 hardware. In that
	 * case we check if we have a possible BPB. If so, then we
	 * assume we have a boot sector instead.
	 */
	sum = 0;
	for (index = 0; index < NDOSPART * DOSPARTSIZE; index++)
		sum += buf[DOSPARTOFF + index];
	if (sum != 0 || !mbr_probe_bpb(buf + 0x0b))
		res = G_PART_PROBE_PRI_NORM;

 out:
	g_free(buf);
	return (res);
}