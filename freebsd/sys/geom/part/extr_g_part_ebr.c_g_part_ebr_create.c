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
typedef  int uint32_t ;
struct g_provider {int sectorsize; int mediasize; int /*<<< orphan*/  consumers; } ;
struct g_part_table {scalar_t__ gpt_depth; int gpt_last; int gpt_entries; int gpt_sectors; scalar_t__ gpt_first; } ;
struct g_part_parms {struct g_provider* gpp_provider; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int EBRSIZE ; 
 int ENOSPC ; 
 int ENXIO ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int g_getattr (char*,struct g_consumer*,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
g_part_ebr_create(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	char type[64];
	struct g_consumer *cp;
	struct g_provider *pp;
	uint32_t msize;
	int error;

	pp = gpp->gpp_provider;

	if (pp->sectorsize < EBRSIZE)
		return (ENOSPC);
	if (pp->sectorsize > 4096)
		return (ENXIO);

	/* Check that we have a parent and that it's a MBR. */
	if (basetable->gpt_depth == 0)
		return (ENXIO);
	cp = LIST_FIRST(&pp->consumers);
	error = g_getattr("PART::scheme", cp, &type);
	if (error != 0)
		return (error);
	if (strcmp(type, "MBR") != 0)
		return (ENXIO);
	error = g_getattr("PART::type", cp, &type);
	if (error != 0)
		return (error);
	if (strcmp(type, "ebr") != 0)
		return (ENXIO);

	msize = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX);
	basetable->gpt_first = 0;
	basetable->gpt_last = msize - 1;
	basetable->gpt_entries = msize / basetable->gpt_sectors;
	return (0);
}