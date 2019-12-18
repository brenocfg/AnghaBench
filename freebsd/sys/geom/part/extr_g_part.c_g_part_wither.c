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
struct g_provider {int /*<<< orphan*/ * private; } ;
struct g_part_table {int /*<<< orphan*/  gpt_entry; } ;
struct g_part_entry {struct g_provider* gpe_pp; } ;
struct g_geom {struct g_part_table* softc; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_PART_DESTROY (struct g_part_table*,int /*<<< orphan*/ *) ; 
 struct g_part_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_part_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GEOM ; 
 int /*<<< orphan*/  g_free (struct g_part_entry*) ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int) ; 
 int /*<<< orphan*/  g_wither_provider (struct g_provider*,int) ; 
 int /*<<< orphan*/  gpe_entry ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_part_wither(struct g_geom *gp, int error)
{
	struct g_part_entry *entry;
	struct g_part_table *table;
	struct g_provider *pp;

	table = gp->softc;
	if (table != NULL) {
		gp->softc = NULL;
		while ((entry = LIST_FIRST(&table->gpt_entry)) != NULL) {
			LIST_REMOVE(entry, gpe_entry);
			pp = entry->gpe_pp;
			entry->gpe_pp = NULL;
			if (pp != NULL) {
				pp->private = NULL;
				g_wither_provider(pp, error);
			}
			g_free(entry);
		}
		G_PART_DESTROY(table, NULL);
		kobj_delete((kobj_t)table, M_GEOM);
	}
	g_wither_geom(gp, error);
}