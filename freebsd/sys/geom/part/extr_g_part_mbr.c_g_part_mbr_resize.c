#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_table {scalar_t__ gpt_last; TYPE_1__* gpt_gp; } ;
struct g_part_parms {int gpp_size; } ;
struct TYPE_5__ {int dp_size; int /*<<< orphan*/  dp_esect; int /*<<< orphan*/  dp_ehd; int /*<<< orphan*/  dp_ecyl; } ;
struct g_part_mbr_entry {TYPE_2__ ent; } ;
struct g_part_entry {scalar_t__ gpe_end; scalar_t__ gpe_start; struct g_provider* gpe_pp; } ;
struct TYPE_6__ {struct g_provider* provider; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int g_debugflags ; 
 scalar_t__ mbr_align (struct g_part_table*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mbr_set_chs (struct g_part_table*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_mbr_resize(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct g_part_parms *gpp)
{
	struct g_part_mbr_entry *entry;
	struct g_provider *pp;
	uint32_t size;

	if (baseentry == NULL) {
		pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
		basetable->gpt_last = MIN(pp->mediasize / pp->sectorsize,
		    UINT32_MAX) - 1;
		return (0);
	}
	size = gpp->gpp_size;
	if (mbr_align(basetable, NULL, &size) != 0)
		return (EINVAL);
	/* XXX: prevent unexpected shrinking. */
	pp = baseentry->gpe_pp;
	if ((g_debugflags & 0x10) == 0 && size < gpp->gpp_size &&
	    pp->mediasize / pp->sectorsize > size)
		return (EBUSY);
	entry = (struct g_part_mbr_entry *)baseentry;
	baseentry->gpe_end = baseentry->gpe_start + size - 1;
	entry->ent.dp_size = size;
	mbr_set_chs(basetable, baseentry->gpe_end, &entry->ent.dp_ecyl,
	    &entry->ent.dp_ehd, &entry->ent.dp_esect);
	return (0);
}