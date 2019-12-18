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
typedef  scalar_t__ u_char ;
struct g_provider {int sectorsize; int mediasize; int /*<<< orphan*/  name; } ;
struct g_part_table {scalar_t__ gpt_depth; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 scalar_t__ DOSMAGIC ; 
 int DOSMAGICOFFSET ; 
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 scalar_t__ DOSPTYP_LDM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int G_PART_PROBE_PRI_HIGH ; 
 int /*<<< orphan*/  LDM_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 size_t LDM_PH_MBRINDEX ; 
 int NDOSPART ; 
 int /*<<< orphan*/  g_free (scalar_t__*) ; 
 int g_getattr (char*,struct g_consumer*,scalar_t__**) ; 
 scalar_t__* g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int,int*) ; 
 int ldm_gpt_probe (struct g_part_table*,struct g_consumer*) ; 
 int* ldm_ph_off ; 
 scalar_t__* ldm_privhdr_read (struct g_consumer*,int,int*) ; 
 scalar_t__ le16dec (scalar_t__*) ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 

__attribute__((used)) static int
g_part_ldm_probe(struct g_part_table *basetable, struct g_consumer *cp)
{
	struct g_provider *pp;
	u_char *buf, type[64];
	int error, idx;


	pp = cp->provider;
	if (pp->sectorsize != 512)
		return (ENXIO);

	error = g_getattr("PART::scheme", cp, &type);
	if (error == 0 && strcmp(type, "GPT") == 0) {
		if (g_getattr("PART::type", cp, &type) != 0 ||
		    strcmp(type, "ms-ldm-data") != 0)
			return (ENXIO);
		error = ldm_gpt_probe(basetable, cp);
		return (error);
	}

	if (basetable->gpt_depth != 0)
		return (ENXIO);

	/* LDM has 1M metadata area */
	if (pp->mediasize <= 1024 * 1024)
		return (ENOSPC);

	/* Check that there's a MBR */
	buf = g_read_data(cp, 0, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);

	if (le16dec(buf + DOSMAGICOFFSET) != DOSMAGIC) {
		g_free(buf);
		return (ENXIO);
	}
	error = ENXIO;
	/* Check that we have LDM partitions in the MBR */
	for (idx = 0; idx < NDOSPART && error != 0; idx++) {
		if (buf[DOSPARTOFF + idx * DOSPARTSIZE + 4] == DOSPTYP_LDM)
			error = 0;
	}
	g_free(buf);
	if (error == 0) {
		LDM_DEBUG(2, "%s: LDM data partitions found in MBR",
		    pp->name);
		/* Read the LDM private header */
		buf = ldm_privhdr_read(cp,
		    ldm_ph_off[LDM_PH_MBRINDEX] * pp->sectorsize, &error);
		if (buf == NULL)
			return (error);
		g_free(buf);
		return (G_PART_PROBE_PRI_HIGH);
	}
	return (error);
}