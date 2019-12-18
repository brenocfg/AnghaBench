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
struct g_provider {int sectorsize; int mediasize; } ;
struct g_part_table {scalar_t__ gpt_last; int /*<<< orphan*/  gpt_sectors; int /*<<< orphan*/  gpt_first; } ;
struct g_part_parms {struct g_provider* gpp_provider; } ;
struct g_part_mbr_table {scalar_t__ mbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOSMAGIC ; 
 scalar_t__ DOSMAGICOFFSET ; 
 int ENOSPC ; 
 int MBRSIZE ; 
 scalar_t__ MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  le16enc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_mbr_create(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_provider *pp;
	struct g_part_mbr_table *table;

	pp = gpp->gpp_provider;
	if (pp->sectorsize < MBRSIZE)
		return (ENOSPC);

	basetable->gpt_first = basetable->gpt_sectors;
	basetable->gpt_last = MIN(pp->mediasize / pp->sectorsize,
	    UINT32_MAX) - 1;

	table = (struct g_part_mbr_table *)basetable;
	le16enc(table->mbr + DOSMAGICOFFSET, DOSMAGIC);
	return (0);
}