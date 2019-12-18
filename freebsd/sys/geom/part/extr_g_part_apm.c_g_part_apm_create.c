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
typedef  void* uint32_t ;
struct g_provider {int sectorsize; int mediasize; } ;
struct g_part_table {scalar_t__ gpt_depth; int gpt_entries; int gpt_first; void* gpt_last; } ;
struct g_part_parms {struct g_provider* gpp_provider; } ;
struct TYPE_4__ {int ent_pmblkcnt; int ent_start; int ent_size; int /*<<< orphan*/  ent_type; int /*<<< orphan*/  ent_name; int /*<<< orphan*/  ent_sig; } ;
struct TYPE_3__ {int ddr_blksize; void* ddr_blkcount; int /*<<< orphan*/  ddr_sig; } ;
struct g_part_apm_table {TYPE_2__ self; TYPE_1__ ddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_DDR_SIG ; 
 int /*<<< orphan*/  APM_ENT_SIG ; 
 char* APM_ENT_TYPE_SELF ; 
 int ENOSPC ; 
 int ENXIO ; 
 void* MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
g_part_apm_create(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_provider *pp;
	struct g_part_apm_table *table;
	uint32_t last;

	/* We don't nest, which means that our depth should be 0. */
	if (basetable->gpt_depth != 0)
		return (ENXIO);

	table = (struct g_part_apm_table *)basetable;
	pp = gpp->gpp_provider;
	if (pp->sectorsize != 512 ||
	    pp->mediasize < (2 + 2 * basetable->gpt_entries) * pp->sectorsize)
		return (ENOSPC);

	/* APM uses 32-bit LBAs. */
	last = MIN(pp->mediasize / pp->sectorsize, UINT32_MAX) - 1;

	basetable->gpt_first = 2 + basetable->gpt_entries;
	basetable->gpt_last = last;

	table->ddr.ddr_sig = APM_DDR_SIG;
	table->ddr.ddr_blksize = pp->sectorsize;
	table->ddr.ddr_blkcount = last + 1;

	table->self.ent_sig = APM_ENT_SIG;
	table->self.ent_pmblkcnt = basetable->gpt_entries + 1;
	table->self.ent_start = 1;
	table->self.ent_size = table->self.ent_pmblkcnt;
	strcpy(table->self.ent_name, "Apple");
	strcpy(table->self.ent_type, APM_ENT_TYPE_SELF);
	return (0);
}