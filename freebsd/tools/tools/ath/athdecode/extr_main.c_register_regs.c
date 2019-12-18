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
typedef  int u_int ;
struct dumpreg {int srevMin; int srevMax; int phyMin; int phyMax; scalar_t__ addr; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {int nregs; struct dumpreg** regs; } ;

/* Variables and functions */
 int MAXREGS ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  qsort (struct dumpreg**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcompar ; 
 TYPE_1__ state ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
register_regs(struct dumpreg *chipregs, u_int nchipregs,
	int def_srev_min, int def_srev_max, int def_phy_min, int def_phy_max)
{
	const int existing_regs = state.nregs;
	int i, j;

	for (i = 0; i < nchipregs; i++) {
		struct dumpreg *nr = &chipregs[i];
		if (nr->srevMin == 0)
			nr->srevMin = def_srev_min;
		if (nr->srevMax == 0)
			nr->srevMax = def_srev_max;
		if (nr->phyMin == 0)
			nr->phyMin = def_phy_min;
		if (nr->phyMax == 0)
			nr->phyMax = def_phy_max;
		for (j = 0; j < existing_regs; j++) {
			struct dumpreg *r = state.regs[j];
			/*
			 * Check if we can just expand the mac+phy
			 * coverage for the existing entry.
			 */
			if (nr->addr == r->addr &&
			    (nr->name == r->name ||
			     (nr->name != NULL && r->name != NULL &&
			     strcmp(nr->name, r->name) == 0))) {
				if (nr->srevMin < r->srevMin &&
				    (r->srevMin <= nr->srevMax &&
				     nr->srevMax+1 <= r->srevMax)) {
					r->srevMin = nr->srevMin;
					goto skip;
				}
				if (nr->srevMax > r->srevMax &&
				    (r->srevMin <= nr->srevMin &&
				     nr->srevMin <= r->srevMax)) {
					r->srevMax = nr->srevMax;
					goto skip;
				}
			}
			if (r->addr > nr->addr)
				break;
		}
		/*
		 * New item, add to the end, it'll be sorted below.
		 */
		if (state.nregs == MAXREGS)
			errx(-1, "too many registers; bump MAXREGS");
		state.regs[state.nregs++] = nr;
	skip:
		;
	}
	qsort(state.regs, state.nregs, sizeof(struct dumpreg *), regcompar);
}