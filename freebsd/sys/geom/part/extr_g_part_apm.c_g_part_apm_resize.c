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
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_table {scalar_t__ gpt_last; TYPE_2__* gpt_gp; } ;
struct g_part_parms {scalar_t__ gpp_size; } ;
struct g_part_entry {scalar_t__ gpe_start; scalar_t__ gpe_end; } ;
struct TYPE_4__ {scalar_t__ ent_size; } ;
struct g_part_apm_entry {TYPE_1__ ent; } ;
struct TYPE_6__ {struct g_provider* provider; } ;
struct TYPE_5__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_MAX ; 

__attribute__((used)) static int
g_part_apm_resize(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct g_part_parms *gpp)
{
	struct g_part_apm_entry *entry;
	struct g_provider *pp;

	if (baseentry == NULL) {
		pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
		basetable->gpt_last = MIN(pp->mediasize / pp->sectorsize,
		    UINT32_MAX) - 1;
		return (0);
	}

	entry = (struct g_part_apm_entry *)baseentry;
	baseentry->gpe_end = baseentry->gpe_start + gpp->gpp_size - 1;
	entry->ent.ent_size = gpp->gpp_size;

	return (0);
}