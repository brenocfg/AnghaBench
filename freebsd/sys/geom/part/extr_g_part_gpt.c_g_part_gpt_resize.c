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
struct g_part_table {int dummy; } ;
struct g_part_parms {scalar_t__ gpp_size; } ;
struct TYPE_2__ {scalar_t__ ent_lba_end; } ;
struct g_part_gpt_entry {TYPE_1__ ent; } ;
struct g_part_entry {scalar_t__ gpe_end; scalar_t__ gpe_start; } ;

/* Variables and functions */
 int g_part_gpt_recover (struct g_part_table*) ; 

__attribute__((used)) static int
g_part_gpt_resize(struct g_part_table *basetable,
    struct g_part_entry *baseentry, struct g_part_parms *gpp)
{
	struct g_part_gpt_entry *entry;

	if (baseentry == NULL)
		return (g_part_gpt_recover(basetable));

	entry = (struct g_part_gpt_entry *)baseentry;
	baseentry->gpe_end = baseentry->gpe_start + gpp->gpp_size - 1;
	entry->ent.ent_lba_end = baseentry->gpe_end;

	return (0);
}