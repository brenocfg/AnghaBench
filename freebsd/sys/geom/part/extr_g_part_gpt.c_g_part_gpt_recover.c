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
struct g_provider {int dummy; } ;
struct g_part_table {scalar_t__ gpt_corrupt; TYPE_1__* gpt_gp; } ;
struct g_part_gpt_table {int dummy; } ;
struct TYPE_4__ {struct g_provider* provider; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_gpt_set_defaults (struct g_part_table*,struct g_provider*) ; 
 int /*<<< orphan*/  gpt_create_pmbr (struct g_part_gpt_table*,struct g_provider*) ; 

__attribute__((used)) static int
g_part_gpt_recover(struct g_part_table *basetable)
{
	struct g_part_gpt_table *table;
	struct g_provider *pp;

	table = (struct g_part_gpt_table *)basetable;
	pp = LIST_FIRST(&basetable->gpt_gp->consumer)->provider;
	gpt_create_pmbr(table, pp);
	g_gpt_set_defaults(basetable, pp);
	basetable->gpt_corrupt = 0;
	return (0);
}