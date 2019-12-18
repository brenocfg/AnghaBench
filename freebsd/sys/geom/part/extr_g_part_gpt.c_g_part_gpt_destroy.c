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
struct g_part_gpt_table {scalar_t__* state; int* lba; int /*<<< orphan*/ * hdr; } ;
struct TYPE_4__ {struct g_provider* provider; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 size_t GPT_ELT_PRIHDR ; 
 size_t GPT_ELT_SECHDR ; 
 scalar_t__ GPT_STATE_OK ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_gpt_destroy(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_part_gpt_table *table;
	struct g_provider *pp;

	table = (struct g_part_gpt_table *)basetable;
	pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
	g_free(table->hdr);
	table->hdr = NULL;

	/*
	 * Wipe the first 2 sectors and last one to clear the partitioning.
	 * Wipe sectors only if they have valid metadata.
	 */
	if (table->state[GPT_ELT_PRIHDR] == GPT_STATE_OK)
		basetable->gpt_smhead |= 3;
	if (table->state[GPT_ELT_SECHDR] == GPT_STATE_OK &&
	    table->lba[GPT_ELT_SECHDR] == pp->mediasize / pp->sectorsize - 1)
		basetable->gpt_smtail |= 1;
	return (0);
}