#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_table {int gpt_smhead; int gpt_smtail; TYPE_1__* gpt_gp; } ;
struct g_part_parms {int dummy; } ;
struct g_part_ldm_table {int db_offset; scalar_t__ is_gpt; } ;
struct TYPE_4__ {struct g_provider* provider; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ENOSYS ; 
 int LDM_DB_SIZE ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int* ldm_ph_off ; 

__attribute__((used)) static int
g_part_ldm_destroy(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_part_ldm_table *table;
	struct g_provider *pp;

	table = (struct g_part_ldm_table *)basetable;
	/*
	 * To destroy LDM on a disk partitioned with GPT we should delete
	 * ms-ldm-metadata partition, but we can't do this via standard
	 * GEOM_PART method.
	 */
	if (table->is_gpt)
		return (ENOSYS);
	pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
	/*
	 * To destroy LDM we should wipe MBR, first private header and
	 * backup private headers.
	 */
	basetable->gpt_smhead = (1 << ldm_ph_off[0]) | 1;
	/*
	 * Don't touch last backup private header when LDM database is
	 * not located in the last 1MByte area.
	 * XXX: can't remove all blocks.
	 */
	if (table->db_offset + LDM_DB_SIZE ==
	    pp->mediasize / pp->sectorsize)
		basetable->gpt_smtail = 1;
	return (0);
}