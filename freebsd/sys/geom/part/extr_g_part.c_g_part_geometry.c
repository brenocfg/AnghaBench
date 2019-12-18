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
typedef  int u_int ;
struct g_part_table {int gpt_fixgeom; int gpt_heads; int gpt_sectors; } ;
struct g_consumer {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ g_getattr (char*,struct g_consumer*,int*) ; 
 int /*<<< orphan*/  g_part_geometry_heads (scalar_t__,int,scalar_t__*,int*) ; 

__attribute__((used)) static void
g_part_geometry(struct g_part_table *table, struct g_consumer *cp,
    off_t blocks)
{
	static u_int candidate_sectors[] = { 1, 9, 17, 33, 63, 0 };
	off_t chs, bestchs;
	u_int heads, sectors;
	int idx;

	if (g_getattr("GEOM::fwsectors", cp, &sectors) != 0 || sectors == 0 ||
	    g_getattr("GEOM::fwheads", cp, &heads) != 0 || heads == 0) {
		table->gpt_fixgeom = 0;
		table->gpt_heads = 0;
		table->gpt_sectors = 0;
		bestchs = 0;
		for (idx = 0; candidate_sectors[idx] != 0; idx++) {
			sectors = candidate_sectors[idx];
			g_part_geometry_heads(blocks, sectors, &chs, &heads);
			if (chs == 0)
				continue;
			/*
			 * Prefer a geometry with sectors > 1, but only if
			 * it doesn't bump down the number of heads to 1.
			 */
			if (chs > bestchs || (chs == bestchs && heads > 1 &&
			    table->gpt_sectors == 1)) {
				bestchs = chs;
				table->gpt_heads = heads;
				table->gpt_sectors = sectors;
			}
		}
		/*
		 * If we didn't find a geometry at all, then the disk is
		 * too big. This means we can use the maximum number of
		 * heads and sectors.
		 */
		if (bestchs == 0) {
			table->gpt_heads = 255;
			table->gpt_sectors = 63;
		}
	} else {
		table->gpt_fixgeom = 1;
		table->gpt_heads = heads;
		table->gpt_sectors = sectors;
	}
}