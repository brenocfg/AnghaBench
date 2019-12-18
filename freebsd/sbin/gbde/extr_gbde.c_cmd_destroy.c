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
struct g_bde_key {int /*<<< orphan*/ * lsector; int /*<<< orphan*/ * mkey; int /*<<< orphan*/  flags; int /*<<< orphan*/  keyoffset; int /*<<< orphan*/  sectorN; int /*<<< orphan*/  sector0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBDE_F_SECT0 ; 
 int G_BDE_MAXKEYS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
cmd_destroy(struct g_bde_key *gl, int nkey)
{
	int i;

	bzero(&gl->sector0, sizeof gl->sector0);
	bzero(&gl->sectorN, sizeof gl->sectorN);
	bzero(&gl->keyoffset, sizeof gl->keyoffset);
	gl->flags &= GBDE_F_SECT0;
	bzero(gl->mkey, sizeof gl->mkey);
	for (i = 0; i < G_BDE_MAXKEYS; i++)
		if (i != nkey)
			gl->lsector[i] = ~0;
}