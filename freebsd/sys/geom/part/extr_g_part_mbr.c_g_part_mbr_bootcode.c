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
typedef  scalar_t__ uint32_t ;
struct g_part_table {int dummy; } ;
struct g_part_parms {scalar_t__ gpp_codesize; int /*<<< orphan*/  gpp_skip_dsn; int /*<<< orphan*/  gpp_codeptr; } ;
struct g_part_mbr_table {scalar_t__ mbr; } ;

/* Variables and functions */
 scalar_t__ DOSDSNOFF ; 
 int /*<<< orphan*/  DOSPARTOFF ; 
 int ENODEV ; 
 scalar_t__ MBRSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_part_mbr_bootcode(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_part_mbr_table *table;
	uint32_t dsn;

	if (gpp->gpp_codesize != MBRSIZE)
		return (ENODEV);

	table = (struct g_part_mbr_table *)basetable;
	dsn = *(uint32_t *)(table->mbr + DOSDSNOFF);
	bcopy(gpp->gpp_codeptr, table->mbr, DOSPARTOFF);
	if (dsn != 0 && !gpp->gpp_skip_dsn)
		*(uint32_t *)(table->mbr + DOSDSNOFF) = dsn;
	return (0);
}