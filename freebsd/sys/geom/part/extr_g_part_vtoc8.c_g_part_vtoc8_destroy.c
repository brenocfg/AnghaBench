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

/* Variables and functions */

__attribute__((used)) static int
g_part_vtoc8_destroy(struct g_part_table *basetable, struct g_part_parms *gpp)
{

	/* Wipe the first sector to clear the partitioning. */
	basetable->gpt_smhead |= 1;
	return (0);
}