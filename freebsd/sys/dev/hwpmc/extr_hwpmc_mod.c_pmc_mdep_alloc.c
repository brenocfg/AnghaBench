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
struct pmc_mdep {int pmd_nclass; } ;
struct pmc_classdep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct pmc_mdep* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmc_soft_initialize (struct pmc_mdep*) ; 

struct pmc_mdep *
pmc_mdep_alloc(int nclasses)
{
	struct pmc_mdep *md;
	int	n;

	/* SOFT + md classes */
	n = 1 + nclasses;
	md = malloc(sizeof(struct pmc_mdep) + n *
	    sizeof(struct pmc_classdep), M_PMC, M_WAITOK|M_ZERO);
	md->pmd_nclass = n;

	/* Add base class. */
	pmc_soft_initialize(md);
	return md;
}