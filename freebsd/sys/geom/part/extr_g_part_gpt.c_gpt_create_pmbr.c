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
struct g_provider {int mediasize; int sectorsize; } ;
struct g_part_gpt_table {scalar_t__ mbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOSMAGIC ; 
 scalar_t__ DOSMAGICOFFSET ; 
 scalar_t__ DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int NDOSPART ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  gpt_write_mbr_entry (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16enc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gpt_create_pmbr(struct g_part_gpt_table *table, struct g_provider *pp)
{

	bzero(table->mbr + DOSPARTOFF, DOSPARTSIZE * NDOSPART);
	gpt_write_mbr_entry(table->mbr, 0, 0xee, 1,
	    MIN(pp->mediasize / pp->sectorsize - 1, UINT32_MAX));
	le16enc(table->mbr + DOSMAGICOFFSET, DOSMAGIC);
}