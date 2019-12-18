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
struct g_part_table {int gpt_smhead; } ;
struct g_part_parms {int dummy; } ;
struct g_part_bsd_table {int /*<<< orphan*/ * bbarea; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_part_bsd_destroy(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_part_bsd_table *table;

	table = (struct g_part_bsd_table *)basetable;
	if (table->bbarea != NULL)
		g_free(table->bbarea);
	table->bbarea = NULL;

	/* Wipe the second sector to clear the partitioning. */
	basetable->gpt_smhead |= 2;
	return (0);
}